#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main(){
	std::vector<int> numbers;
	std::vector<std::string> lines;

	std::string name;
	std::cin >> name;
	std::ifstream ist {name};
	if (!ist){
		std::cerr << "File error";
		return;
	}
	std::string goal;
	std::cin >> goal;

	std::string str;

	for (int i = 0; true; ++i){
		getline(ist, str);
		if (!ist) 
			break;
		
		std::istringstream istr {str};
		std::string word;
		while (istr >> word){
			if (word == goal){
				numbers.push_back(i);
				lines.push_back(str);
				break;
			}
		}
	}

	for (int i = 0; i < numbers.size(); ++i){
		std::cout << numbers[i] << ": " << lines[i] << '\n';
	}
}
