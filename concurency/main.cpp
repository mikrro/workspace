#include <csignal>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

void work1(){
    std::cout << "Hello from work1 \n";
}

void work2(){
    std::cout << "Hello from work2 \n";
}

void t_join(std::thread &t) {
    if(t.joinable())
        t.join();
}

void t_join_2(std::thread t) {
    if(t.joinable())
        t.join();
}

void t_detach(std::thread t) {
    if(t.joinable())
        t.detach();
}

void signal_handler(int signal) {
    switch(signal) {
        case SIGABRT:
            std::cerr << "SIGABRT received\n";
            break;
        case SIGTERM:
            std::cerr << "SIGTERM received\n";
            break;
        case SIGHUP:
            std::cerr << "SIGHUP received\n";
            break;
        default:
            std::cerr << "Unexpected signal " << signal << " received\n";
    }
    std::_Exit(EXIT_FAILURE);
}

std::thread f() {
    std::thread t(work1);
    return t;
}

void test1(){
    std::signal(SIGABRT, signal_handler);
    std::signal(SIGTERM, signal_handler);
    std::signal(SIGHUP, signal_handler);

    std::thread t1(work1);
    std::thread t2 = std::move(t1);
    t1 = std::thread(work2);
    std::thread t3 = f();

    t_join(t1);
    t_join(t2);
    t_join_2(std::thread(work2));
    t_join(t3);
}


class thread_guard {
    std::thread &t;
public:
    explicit thread_guard(std::thread &t_)
            : t(t_) {
        std::cout << "Hello for new thread " << t.get_id() << std::endl;

        //if(!t.joinable())
         //   throw std::logic_error("Not a thread");

    }
    ~thread_guard(){
        std::cout << "bye!\n";

        if(t.joinable())
            t.join();
    }
    thread_guard(thread_guard const&) = delete;
    thread_guard & operator=(thread_guard const&) = delete;

};

class scoped_thread {
    std::thread t;
public:
    explicit scoped_thread(std::thread t_)
            : t(std::move(t_)) {
        std::cout << "Hello for new thread " << t.get_id() << std::endl;

        if(!t.joinable())
           throw std::logic_error("Not a thread");

    }
    ~scoped_thread(){
        std::cout << "bye!\n";
        t.join();
    }

    scoped_thread(scoped_thread const&) = delete;
    scoped_thread& operator=(scoped_thread const&) = delete;

};

struct func {
    int &i;
    func(int &i_) : i(i_){};

    void operator()(){
        for(uint a=0; a<100000; a++);
        std::cout << "DONE\n";
    }
};

void log(std::string f) {
    std::cout << "inside " << f << std::endl;
}

void fun_with_state(int &state) {
    log(__func__);
}

void test2(){
    int some_state = 1;

    func my_func(some_state);
    std::thread t(my_func);
    thread_guard g(t);
    scoped_thread s{std::thread(my_func)};

    work1();
}

void work3(int i) {
    std::string s = __func__ + ' ' + std::to_string(i);
    log(s);
}
void test3(int N = 10) {
    std::vector<std::thread> threads;
    for(int i = 0; i < N; i++) {
        threads.push_back(std::thread(work3, i));
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

}

int main() {

    std::cout << std::thread::hardware_concurrency() << std::endl;
    test3(std::thread::hardware_concurrency());
    return 0;
}