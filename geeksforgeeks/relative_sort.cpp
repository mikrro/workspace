#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

void sort(const int* a1, const int m, const int* a2, const int n, int* out) {
    std::vector<int> rest;
    std::map<int, int> count_map;

    for(int i = 0; i < n; i++) 
        count_map[a2[i]] = 0;
        
    for(int i = 0; i < m; i++) {
        if(count_map.find(a1[i]) != count_map.end()) 
            count_map[a1[i]]++;
        else
            rest.push_back(a1[i]);
    }
    
    std::sort(rest.begin(), rest.end());
    
    int k = 0;
    for(int i = 0; i < n; i++) {
        while(count_map[a2[i]]-- > 0) {
            out[k++] = a2[i];
        }
    }
    
    for(int i = 0; i < rest.size(); i++) {
        out[k++] = rest[i];
    }
}

int main() {
	
	int t, n, m;
	int a1[50], a2[10], out[50];
	
	cin >> t;
	
	while(t--) {
	    cin >> m;
	    cin >> n;
	    for(int i = 0; i < m; i++) {
	        cin >> a1[i];
	    }
	    for(int i = 0; i < n; i++) {
	        cin >> a2[i];
	    }
	    
	    if(n > 0 && m > 0 && m >= n)
	       sort(a1, m, a2, n, out);
	       
	    for(int i = 0; i < m; i++) {
	        cout << out[i] << " ";
	    }
	    cout << endl;
	}
	return 0;
}