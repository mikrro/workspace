#include <iostream>
using namespace std;

int pow(const int A, const int B, const int C) {
    if(B == 0) {
        return 1;
    } 
    if(B == 1) {
        return A % C;
    }
    
    int r = pow(A, B/2, C);
    if(B % 2 == 0) {
        return (r * r) % C;
    }
    return (((r * r) % C) * A % C) % C;
}

int main() {
	
	int t, A, B, C;
	
	cin >> t;
	while(t--) {
	    cin >> A;
	    cin >> B;
	    cin >> C;
	    cout << pow(A, B, C) << endl;
	}
	
	return 0;
}