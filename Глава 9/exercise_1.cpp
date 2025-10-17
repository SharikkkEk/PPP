#include <fstream>
#include <iostream>

int main(){
	std::ifstream ist {"1.txt"};
	if (!ist){
		std::cout << "file error";
	}

	std::ofstream ost {"1.2.txt"};
	char ch;
	while (ist >> ch){
		ost << ch;
	}
}
