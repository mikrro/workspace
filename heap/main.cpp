#include <iostream>
#include <vector>
#include <list>
#include <memory>

struct k_elem {
    int k_index;
    int elem;
    k_elem(int k, int e) : k_index(k), elem(e) {}
};

typedef std::shared_ptr<k_elem> heap_elem_t;
typedef std::vector<heap_elem_t> heap_t;

void swap_heap(heap_t &heap, int i, int j) {
    heap_elem_t temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

int parent(int i) {
    if (i == 0) {
        return 0;
    }

    return (int)(i/2.0 - 0.5);
}

void heap_insert(heap_t &heap, heap_elem_t elem) {
    heap.push_back(elem);
    int i = heap.size() - 1;
    while(i > 0 && heap[parent(i)]->elem > heap[i]->elem) {
        swap_heap(heap, i, parent(i));
        i = parent(i);
    }
}

void min_heapify(heap_t &heap, int i) {
    int left = 2*(i+1)-1;
    int right = 2*(i+1);
    int smallest = i;
    if(left < heap.size() && heap[left]->elem < heap[i]->elem)
        smallest = left;
    if(right < heap.size() && heap[right]->elem < heap[smallest]->elem)
        smallest = right;
    if(i != smallest) {
        swap_heap(heap, i, smallest);
        min_heapify(heap, smallest);
    }
}

heap_elem_t min_elem(heap_t &heap) {
    heap_elem_t min = heap[0];
    heap[0] = heap[heap.size()-1];
    heap.pop_back();
    min_heapify(heap,0);
    return min;
}

int main() {
    std::vector<std::list<int> > k_lists(3);
    k_lists[0] = {0,1,8,10,15};
    k_lists[1] = {3,4,6};
    k_lists[2] = {2,7,9,12};
    std::list<int> list;
    int N = 0;
    heap_t heap;

    for(int i = 0; i < k_lists.size(); i++) {
        N += k_lists[i].size();

        heap_insert(heap, heap_elem_t(new k_elem(i, *k_lists[i].begin())));
        k_lists[i].pop_front();
    }

    while(list.size() <  N) {
        heap_elem_t min = min_elem(heap);
        if(!k_lists[min->k_index].empty()){
            heap_insert(heap, heap_elem_t(new k_elem(min->k_index, *k_lists[min->k_index].begin())));
            k_lists[min->k_index].pop_front();
        }
        list.push_back(min->elem);
    }

    for(auto e : list) {
        std::cout << e << "\t";
    }
    std::cout << std::endl;
    return 0;
}