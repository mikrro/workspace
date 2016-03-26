#include <iostream>
#include <map>
#include <list>
#include <memory>

struct Node;
typedef std::shared_ptr<Node> NodePtr;

struct Node {
    Node(int k, NodePtr n, NodePtr p) : key(k), next(n), prev(p) {}
    int key;
    NodePtr next, prev;
};

class LRUCache{
public:
    LRUCache(int capacity) {
        capacity_ = capacity;
        LRU = nullptr;
        LRU_end = nullptr;
    }

    int get(int key) {
        std::cout << "value of " << key << "\t";
        auto value = cache.find(key);
        if(value == cache.end()) {
            return -1;
        }
        return value->second;
    }

    void set(int key, int value) {
        std::cout << "set(" << key << ", " << value << ")\n";
        if(cache.find(key) == cache.end()) {
            if(cache.size() == capacity_) {
                eraseLRU();
            }
            cache[key] = value;
            insertLRU(key);
            return;
        }
        cache[key] = value;
        updateLRU(key);
    }

private:
    std::map<int,int> cache;
    std::map<int,NodePtr> LRU_cache;
    NodePtr LRU, LRU_end;

    int capacity_;

    void eraseLRU() {
        if(LRU_end) {
            int key = LRU_end->key;
            cache.erase(cache.find(key));
            LRU_cache.erase(LRU_cache.find(key));
            if(LRU == LRU_end) {
                LRU = nullptr;
                LRU_end = nullptr;
                return;
            }
            LRU_end = LRU_end->prev;
            if(LRU_end) {
                LRU_end->next = nullptr;
            }
        }
    }

    void updateLRU(int key) {
        NodePtr node = LRU_cache[key];
        if(node == LRU) {
            return;
        }

        if(node == LRU_end) {
            if(node->prev) {
                LRU_end = node->prev;
            }
            LRU_end = nullptr;
        }

        if(node->prev) {
            node->prev->next = node->next;
        }
        if(node->next) {
            node->next->prev = node->prev;
        }

        node->prev = nullptr;
        node->next = LRU;
        if(LRU) {
            LRU->prev = node;
        }
        LRU = node;
        LRU_cache[key] = LRU;
    }

    void insertLRU(int key) {
        NodePtr node = NodePtr(new Node(key, LRU, nullptr));
        if(LRU) {
            LRU->prev = node;

        } else {
            LRU_end = node;
        }
        LRU = node;
        LRU_cache[key] = node;
    }
};

int main() {

    LRUCache cache(1);
    cache.set(2,2);
    std::cout << cache.get(2) << std::endl;

    cache.set(1,1);
    std::cout << cache.get(1) << std::endl;
    std::cout << cache.get(2) << std::endl;

    cache.set(4,4);

    std::cout << cache.get(1) << std::endl;
    std::cout << cache.get(2) << std::endl;
    std::cout << cache.get(4) << std::endl;

    cache.set(4,3);

    std::cout << cache.get(1) << std::endl;
    std::cout << cache.get(2) << std::endl;
    std::cout << cache.get(4) << std::endl;


    cache.set(5,5);

    std::cout << cache.get(1) << std::endl;
    std::cout << cache.get(2) << std::endl;
    std::cout << cache.get(4) << std::endl;
    std::cout << cache.get(5) << std::endl;


    return 0;
}