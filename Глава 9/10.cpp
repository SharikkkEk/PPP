#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string& s, const std::string& term){
	std::istringstream ist {s};
	std::vector<std::string> vector;
	
	std::string temp;
	std::string str;
	while (ist >> temp){
		int pos = temp.find(term);
		if (pos == 0){
			vector.push_back(str);
			str = temp.erase(0, term.size());
		} else 
			str += temp;
	}
	if (str.size() != 0)
		vector.push_back(str);
		
	return vector;
}

int main(){
	auto v = split("ABC1 DFGABC2 DFGABC3 DFGABC4", "DFG");
	for (auto x : v)
		std::cout << x << ' ';
}

