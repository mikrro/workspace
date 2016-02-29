#include <iostream>
#include <limits>
#include <functional>
#include <vector>
#include <cmath>
#include <set>
#include <fstream>


int sum(int a, int N) {
    int number_of_a = N/a;
    return 0.5*number_of_a*(number_of_a+1)*a;
}

int sum_of_2_numbers(int a, int b, int N) {
    return sum(a, N) + sum(b, N) - sum(a*b, N);
}

int fib(int i, std::vector<int> &tab) {
    if(i > 1 && tab[i] == 0)
        tab[i] = fib(i-1, tab) + fib(i-2, tab);
    return tab[i];
}

int memoization(const int i) {
    std::vector<int> tab(i+1);
    std::fill(tab.begin(), tab.end(), 0);
    tab[1] = 1;
    return fib(i, tab);
}

int dynamic_fib(int n) {
    int a = 0;
    int b = 1;
    int temp = 0;
    for(int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

typedef unsigned long long int ullint;
ullint sum_of_fib(ullint N) {
    ullint a = 1;
    ullint fib = 1;
    ullint sum = 0;
    ullint temp ;
    while(fib < N) {
        if (fib % 2 == 0)
            sum += fib;
        temp = a;
        a = fib;
        fib += temp;
    }
    std::cout << "last fib " << fib << std::endl;
    return sum;
}

void FermatFactor(long int N, std::set<long int> &v){

    long double x = floor(sqrt(N)) ;
    long double y = sqrt(x*x-N);
    while (std::floor(y) != y) {
        x++;
        y = sqrt(x*x-N);
    }
    long int a = x+y;
    long int b = x-y;

    if(b == 1) {
        v.insert(a);
        return;
    }
    while( a % 2 == 0) a /= 2;
    while( b % 2 == 0) b /= 2;
    FermatFactor(a,v);
    FermatFactor(b,v);
}

void factorize(long int N) {
    std::set<long int> v;
    FermatFactor(N,v);
    for(auto a : v)
        std::cout << a << "\t" ;
    std::cout << std::endl;
}
int createPalindrom(int firstPart) {
    int secondPart = 0;
    int temp = firstPart;
    for(int i = 0 ; i < 3; i++) {
        int remainPart = temp%10;
        secondPart = secondPart*10 + remainPart;
        firstPart *= 10;
        temp /= 10;
    }
    return firstPart + secondPart;
}

int findPalindrom() {
    int firstHalf = 998;
    while(true) {
        double palindrom = createPalindrom(firstHalf);
        for (int i = 999; i > 99; i--) {
            if( palindrom/ i > 999 || i * i < palindrom)
                break;
            double y = palindrom/ i;
            if(std::floor(y) == palindrom/i ) {
                std::cout << y << "\t" << i << std::endl;
                return palindrom;
            }
        }
        firstHalf--;
    }
}

long double dif(int n) {
    return 1.0/2.0*n*(n+1)*(1.0/2.0*n*(n+1)-1.0/3.0*(2*n+1));
}

double calculateNumOfPrimes(int n) {
    return n / log(n);
}

bool FermatFactorPrimes(long int N){

    long double x = floor(sqrt(N)) ;
    long double y = sqrt(x*x-N);
    while (std::floor(y) != y) {
        x++;
        y = sqrt(x*x-N);
    }
    long int a = x+y;
    long int b = x-y;
    return b == 1;
}

int awasomePrime(int N) {
    int h_range = 128;
    int l_range;
    int step = 2;
    while(calculateNumOfPrimes(h_range) < N)
        h_range *= step;
    l_range = h_range/step;
    int diff = 20;
    while(h_range - l_range > diff) {
        int temp = std::floor((l_range + (h_range - l_range) / 2));
        if(calculateNumOfPrimes(temp) < N)
            l_range = temp;
        else
            h_range = temp;
    }

    std::cout << l_range << "\t" << h_range << std::endl;
    std::cout << calculateNumOfPrimes(l_range) << "\t" << calculateNumOfPrimes(h_range) << std::endl;
    if(l_range % 2 == 0) l_range++;
    for(;l_range <= h_range; l_range += 2)
        if(FermatFactorPrimes(l_range))
            return l_range;

    return -1;
}

long long int prime10001() {
    long long int sum = 0;
    long long int prime = 1;
    while(prime < 2000000) {
        if(FermatFactorPrimes(prime)) {
           // std::cout << prime << std::endl;
            sum += prime;
        }
        prime += 2;
    }
    return sum;
}

long long int calcProduct(std::vector<int>::iterator& b, std::vector<int>::iterator& e,
                          std::vector<int>::iterator end){
    int index = 0;
    long long int product = 1;
    while(index < 13 && e != end) {
        if(*e == 0) {
            product = 1;
            index = 0;
            b = ++e;
        } else {
            product *= *e;
            index++;
            e++;
        }
    }
    if(index < 13)
        return 0;
    return product;
}
long long int biggestProduct(std::string name) {
    std::fstream file(name);
    char c;
    std::vector<int> number;
    if(file.bad())
        return 0;

    while(!file.eof()) {
        file.get(c);
        if(std::isdigit(c)) {
            number.push_back(c - '0');
        }
    }
    std::cout << std::endl ;
    long long int product;
    long long int b_product;
    std::vector<int>::iterator e = number.begin();
    std::vector<int>::iterator b = number.begin();
    std::vector<int>::iterator end = number.end();
    product = calcProduct(b, e, end);
    if(product == 0)
        return 0;
    b_product = product;
    while(e != end){
        if(*e == 0) {
            product = calcProduct(b, e, end);
        } else {
            product *= *e;
            product /= *b;
            b++; e++;
        }
        if(product > b_product)
           b_product = product;
    }
    std::cout << std::endl;
    return b_product;
}

typedef
std::array<std::array<int, 2>, 2> array;

void printM(array &x) {
    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            std::cout << x[i][j] << "\t";
        std::cout << std::endl;
    }
}

array mult(const array &a, const array &b) {
    array r;
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++) {
            r[i][j] = 0;
            for (int k = 0; k < 2; k++)
                r[i][j] += a[i][k] * b[k][j];
        }
    //printM(r);
    return r;
}

array pow(array x, int n, array &I) {
    if(n == 0) return I;
    if(n == 1) return x;
    array y;
    y = pow(x, (int)n/2, I);
    y = mult(y,y);
    if(n % 2)
        y = mult(x,y);
    return y;
};

int fibM(int n){
    array x; x[0] = {1, 1}; x[1] = {1, 0};
    array I; I[0] = {1, 0}; I[1] = {0, 1};

   // printM(x); printM(I);
    return pow(x,n,I)[0][1];
}

void test(){

    std::cout << sum_of_2_numbers(3,5,999) << std::endl;
    std::cout << sum_of_fib(4000000) << std::endl;
    factorize(13195);
    factorize(600851475143);
    std::cout << findPalindrom() << std::endl;
    std::cout << dif(10) << std::endl;
    std::cout.precision(20);
    std::cout << dif(100) << std::endl;
    //std::cout << prime10001() << std::endl;
    std::cout << biggestProduct("/home/paulina/ClionProjects/EulerProb1/Problem8") << std::endl;
}

int main() {

    /*
    for(int i = 0; i < 100; i++)
        std::cout << fibM(i) << "\t" << dynamic_fib(i) << std::endl;
*/
    std::cout << prime10001() << std::endl;
    return 0;
}