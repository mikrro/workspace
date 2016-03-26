#include <iostream>
#include <vector>
#include <list>


std::vector<int> counting_sort(const std::vector<int> &A, int k)
{
    std::vector<int> B(A.size());
    std::vector<int> C(k, 0);

    for(int i = 0; i < A.size(); i++) {
        C[A[i]]++;
    }

    for(int i = 1; i < k; i++) {
        C[i] += C[i-1];
    }

    for(int i = A.size() - 1; i >= 0; i--) {
        B[C[A[i]]-1] = A[i];
        C[A[i]]--;
    }

    return std::move(B);
}

int main() {

    std::vector<int> A = {2,3,6,7,1,8,4,5,9,3};

    std::vector<int> B = counting_sort(A,10);

    std::cout << std::endl;

    for(int b : B) {
        std::cout << b << "\t";
    }

    std::cout << std::endl;

    return 0;
}