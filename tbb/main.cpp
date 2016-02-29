#include <iostream>
#include <cmath>

#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <tbb/parallel_scan.h>

void foo(float e) {
    std::cout << e << std::endl;
}

class ApplyFoo {
    float *m_a;
public:
    ApplyFoo(float *a) : m_a(a) {}
    void operator()(tbb::blocked_range<size_t> &r) const {
        float *a = m_a;
        for(size_t i = r.begin(); i != r.end(); i++)
            a[i] = i;
    }
};

float foo_sum(float f){
    return f;
}

class SumFoo {
    float *m_a;
public:
    float m_sum;
    void operator()(const tbb::blocked_range<size_t> &r) {
        float *a = m_a;
        float sum = m_sum;
        for(size_t i = r.begin(); i != r.end(); i++)
            sum += foo_sum(a[i]);
        m_sum = sum;
    }
    SumFoo(float *a) : m_a(a), m_sum(0) {}
    SumFoo(SumFoo &x, tbb::split) : m_a(x.m_a), m_sum(0) {}
    void join(const SumFoo &y) { m_sum += y.m_sum; }
    float getSum() { return m_sum; }
};

template<typename T>
class Body {
    T reduced_result;
    T* const y;
    const T* const x;
public:
    Body(T y_[], const T x_[]) : reduced_result(0), x(x_), y(y_) {}

    T get_reduced_result() { return reduced_result; }

    template<typename Tag>
    void operator()(const tbb::blocked_range<int> &r, Tag) {
        T temp = reduced_result;
        for(int i = r.begin(); i != r.end(); i++) {
            temp = temp - x[i];
            if(Tag::is_final_scan())
                y[i] = temp;
        }
        reduced_result = temp;
    }

    Body(Body &body, tbb::split) : x(body.x), y(body.y), reduced_result(0) {}
    void reverse_join(Body &a) {reduced_result -= a.reduced_result; }
    void assign(Body &b) { reduced_result = b.reduced_result; }
};

int main() {
    const size_t n = 1000;
    float tab[n], ba[n];
    tbb::parallel_for(tbb::blocked_range<size_t>(0,n), ApplyFoo(tab));
    SumFoo sf = SumFoo(tab);
    tbb::parallel_reduce(tbb::blocked_range<size_t>(0,n), sf);
    std::cout << "SUM " << sf.getSum() << std::endl;

    std::memset(ba, 0, n * sizeof(float));
    Body<float> b(tab,ba);
    tbb::parallel_scan(tbb::blocked_range<int>(0,n,1000), b);
    std::cout << "REDUCE result " << b.get_reduced_result() << std::endl;

    return 0;
}