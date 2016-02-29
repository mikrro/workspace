#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <map>

using namespace std;

bool validate_sequence( const int N, const std::vector<int> &data ) {
	if (data.size() != N) return false;

	std::vector<bool> possible_differences(N-1, true);
	int count_unique_differ = 0;
	for ( int i = 0; i < data.size() - 1 ; i++) {
		if ( possible_differences[abs(data[i] - data[i+1])] ) {
			possible_differences[abs(data[i] - data[i+1])] = false;
			count_unique_differ++;
		} else {
			return false;
		}
	}
	if (count_unique_differ != N-1)
		return false;
	return true;
}

void validate_jolly(const std::vector<int> &data ) {
	std::cout << (validate_sequence(data.size(), data) ? "jolly" : "not jolly") << std::endl;
}

auto proccess_dict( std::vector<std::string> & dict ) {
	std::map<int, std::list<std::string> >  result_dict;
	auto end = result_dict.end();
	for(std::string &word : dict)
		result_dict[word.size()].push_back(word);
	return result_dict;
}


int main() {

	std::vector<std::string> dict = {"and","dick","jane","puff","spot","yertle"};
	std::map<int, std::list<std::string> > map = std::move(proccess_dict(dict));
	for(auto &m : map) {
		for(auto &l : m.second)
			std::cout << m.first << "->" << l << std::endl;
	}
    return 0;
}