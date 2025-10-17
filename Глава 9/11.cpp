#include <fstream>
#include <vector>
#include <iostream>



int main(){
	std::ifstream ist {"11.txt"};
	std::string res;

	for (char ch = 0; ist.get(ch);)
		res.push_back(ch);

	std::ofstream ost {"11.txt"};
	
	for (auto it = res.end()-1; it != res.begin()-1; it--)
		ost << *it;
}
