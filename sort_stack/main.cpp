#include <iostream>
#include <stack>

int main() {
    std::stack<int> src, dest;
    int n = 10;

    for(int i = 0; i < n; i++) {
        int num = rand() % n;
        src.push(num);
        std::cout << num << std::endl;
    }
    std::cout << "END" << std::endl;

    dest.push(src.top());
    src.pop();

    while(!src.empty()) {
        if(dest.top() >= src.top()){
            dest.push(src.top());
            src.pop();
        } else {
            int temp = src.top();
            src.pop();
            while( !dest.empty() && dest.top() < temp ) {
                src.push(dest.top());
                dest.pop();
            }
            dest.push(temp);
        }
    }

    while(!dest.empty()) {
        std::cout << dest.top() << std::endl;
        dest.pop();
    }

    return 0;
}