#include <iostream>
#include <vector>
#include <sstream>

std::vector<std::string> split(const std::string s){
	std::istringstream ist {s};
	std::vector<std::string> vector;
	
	std::string str;
	while (ist >> str)
		vector.push_back(str);
	return vector;
}

int main(){
	auto s = "ABC ABC ABC ABC";
	for (auto x : split(s)){
		std::cout << x << ' ';
	}
}
