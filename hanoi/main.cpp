#include <iostream>
#include <stack>
#include <vector>
#include <memory>

struct Tower : std::enable_shared_from_this<Tower> {
    int index;
    std::stack<int> disks;
public:
    Tower(int i) : index(i) {}
    void add(int d) {
        if(!disks.empty() && disks.top() <= d) {
            std::cerr << "zonk\n";
            return;
        }
        //std::cout << " Push disk " << d << " to tower" << index << std::endl;
        disks.push(d);
    }

    int getIndex() {return index;}
    void moveToTop(std::shared_ptr<Tower> t) {
        if(disks.empty()) {
            std::cout << " Couldn't move disk from " << index
            << " to " << t->getIndex() << " - empty tower " << std::endl;
            return;
        }
        int top = disks.top();
        disks.pop();
        t->add(top);
        std::cout << " Move disk " << top << " from " << index
                  << " to " << t->getIndex() << std::endl;
    }

    void moveDisks(int n, std::shared_ptr<Tower> destination, std::shared_ptr<Tower> buffer) {
        if (n > 0) {
            moveDisks(n-1, buffer, destination);
            moveToTop(destination);
            buffer->moveDisks(n-1, destination, shared_from_this());
        }
    }

    void print() {
        std::cout << "Listing of tower " << index << std::endl;
        while(!disks.empty()) {
            std::cout << disks.top() << std::endl;
            disks.pop();
        }
    }
};

int main() {
    int n = 5;
    std::vector<std::shared_ptr<Tower>> towers;
    for(int i = 0; i < 3; i++)
        towers.push_back(std::shared_ptr<Tower>(new Tower(i)));

    for(int i = n - 1; i >= 0; i--)
        towers[0]->add(i);

    for(auto tower : towers)
        tower->print();

    for(int i = n - 1; i >= 0; i--)
        towers[0]->add(i);

    towers[0]->moveDisks(n, towers[2], towers[1]);

    for(auto &tower : towers)
        tower->print();

    return 0;
}