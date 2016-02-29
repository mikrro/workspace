#include <iostream>
#include <vector>

int exch(std::vector<int> &tab, int i, int j) {
    int temp = tab[i];
    tab[i] = tab[j];
    tab[j] = temp;
}

int partition(std::vector<int> &tab, int lo, int hi) {
    int i = lo;
    int j = hi+1;
    while(true) {
        while((tab[++i] < tab[lo]) && (i < hi));
        while((tab[--j] > tab[lo]) && (j > lo));
        if(i >= j) break;
        exch(tab,i,j);
    }
    exch(tab,lo,j);
    return j;
}

void quicksort(std::vector<int> &tab, int lo, int hi) {

    if (hi <= lo)
        return;

    int j = partition(tab,lo,hi);
    quicksort(tab,lo,j-1);
    quicksort(tab,j+1,hi);
}

void merge(std::vector<int> &a, std::vector<int> &aux, int lo, int hi, int mid) {
   // std::cout << "MERGE " << lo << ", " << mid << ", " << hi << std::endl;
    for(int k = lo; k <= hi; k++)
        aux[k] = a[k];
    int i = lo; int j = mid+1;
    for(int k = lo; k <= hi; k++) {
        if(i > mid) a[k] = aux[j++];
        else if(j > hi) a[k] = aux[i++];
        else if(aux[j] < aux[i]) a[k] = aux[j++];
        else a[k] = aux[i++];
    }
}

void mergesort(std::vector<int> &a, std::vector<int> &aux, int lo, int hi) {
    if (hi <= lo) return;
    int mid = lo + (hi-lo)/2;
    mergesort(a,aux,lo,mid);
    mergesort(a,aux,mid+1,hi);
    merge(a,aux,lo,hi,mid);
}

void mergesort(std::vector<int> &a) {
    std::vector<int> aux(a.size());
    mergesort(a,aux,0,a.size()-1);
}

bool exists(int i) {
    return i < 1000;
}

int find_size() {
    int i = 1;
    while(exists(i)) i*= 2;
    if(i == 1)
        if(exists(0))
            return 1;
        else
            return 0;

    int j = i/2;
    int index = j + (i-j)/2;

    while((i-j) > 1){
        if(exists(index))
            j = index;
        else
            i = index;
        index = j + (i-j)/2;
    }
    return j;
}

int main() {
    std::vector<int> tab = {2,4,9,1,0,3,2,5,4,6};

    quicksort(tab,0,10);
    mergesort(tab);

    for(auto &a : tab)
        std::cout << a << "\t";

    std::cout << std::endl << find_size();
    return 0;
}