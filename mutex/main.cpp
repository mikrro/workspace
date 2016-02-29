#include <iostream>
#include <thread>
#include <mutex>

class some_big_object {
    int ID;
public:
    some_big_object(int id) : ID(id) {};
    void print() {
        std::cout << "ID " << ID << std::endl;
    }

    void setID(int ID) {
        some_big_object::ID = ID;
    }

    int getID() const {
        return ID;
    }
};

void swap(some_big_object& lhs, some_big_object &rhs) {
    std::cout << std::this_thread::get_id() << " Before swap \n" ;
    lhs.print();
    rhs.print();
    int id = lhs.getID();
    lhs.setID(rhs.getID());
    rhs.setID(id);

    std::cout << std::this_thread::get_id() << " After swap \n" ;
    lhs.print();
    rhs.print();

}

class X {
    some_big_object some_detail;
    std::mutex m;
public:
    X(some_big_object &sd) : some_detail(sd) {}

    friend void swap_X(X &lhs, X &rhs);
};

void swap_X(X &lhs, X &rhs) {
    if(&lhs == &rhs)
        return;
    std::lock(lhs.m, rhs.m);
    std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
    swap(lhs.some_detail, rhs.some_detail);
    std::cout << std::this_thread::get_id() << " Before swap \n" ;
}

void test(){
    some_big_object A(1), B(2);
    X x1(A), x2(B);
    std::thread t1(swap_X, std::ref(x1), std::ref(x2));
    std::thread t2(swap_X, std::ref(x1), std::ref(x2));
    t1.join();
    t2.join();

}

int main() {

    test();
    return 0;
}