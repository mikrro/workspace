#include <iostream>
#include <vector>
#include <cmath>

int digit(int n, int i)
{
    if(n < pow(10,i)) {
        return -1;
    }

    return (int)(n/pow(10,i)) % 10;
}

int get_count(int n)
{
    int count = 0;
    int i = 1;
    int a = 1;
    bool is_non_zero = digit(n, i-1) > 0;
    int d = digit(n, i);
    while(d != -1){
        count += a*d;
        if((i-2) >= 0) {
            if(is_non_zero)
                count += (a-1);
            else
                count += (n % (a * 10)) * d;
        }
        i++;
        a *= 10;
        is_non_zero = d > 0;
        d = digit(n,i);
    }
    return count;
}

int main() {
    std::vector<int> vec = {9, 107, 155, 1000};
    for( auto n : vec)
        std::cout << get_count(n) << std::endl;
    return 0;
}