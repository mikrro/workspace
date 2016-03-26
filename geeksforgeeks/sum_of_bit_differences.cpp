#include <iostream>
#include <vector>
using namespace std;

int diff(const int *tab, int n) {
    
    std::vector<int> lut(sizeof(int)*8, 0);
    
    for(int i = 0; i < n; i++) {
        int k = 0;
        int a = tab[i];
        
        while(a > 0) {
            lut[k++] += (a & 1);
            a /= 2;
        }
    }
    
    int count = 0;
    for(int i = 0; i < lut.size(); i++) {
        count += lut[i] * (n - lut[i]); 
    }
    return count * 2;
}

int main() {
	
	int t, n;
	int a[10];
	
	cin >> t;
	
	while(t--) {
	   cin >> n;
	   for(int i = 0; i < n; i++) 
	       cin >> a[i];
	   
	   cout << diff(a, n) << endl;
	}
	return 0;
}