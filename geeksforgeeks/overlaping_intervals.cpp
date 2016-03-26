#include <iostream>
#include <map>
using namespace std;

int main() {
	
	
	int t, n, x, y;
	std::map<int, int> intervals;
	std::map<int, int>::iterator i, j, temp;
	
	cin >> t;
	while(t--) {
	    cin >> n;
	    
	    intervals.clear();
	    for(int i = 0; i < n; i++) {
	        cin >> x;
	        cin >> y;
	        if(intervals.find(x) != intervals.end()){
	            if(intervals[x] < y) 
	                intervals[x] = y;
	        } else {
	            intervals[x] = y;
	        }
	    }
	    
	    i = intervals.begin();
	    j = ++intervals.begin();
	    while(j != intervals.end()) {
	        if(i->second >= j->first) {
	            if(i->second <= j->second) {
    	            i->second = j->second;
	            } 
	            temp = j++;
    	        intervals.erase(temp);  
	        } else { 
	            i = j++;
	        }
	    }
	   
	    i = intervals.begin();
	    for(; i != intervals.end(); i++) {
	        cout << i->first << " " << i->second << " ";
	    }
	    cout << endl;
	}
	
	return 0;
}