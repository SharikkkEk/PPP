#include <iostream>
#include <fstream>
#include <iomanip>

int main(){
	std::ifstream ist {"numbers.txt"};
	std::ofstream ost {"14.txt"};
	ost << std::scientific << std::setprecision(8);
	
	while (ist && ost){
		double n = 0;
		for (int i = 0; i < 20 && (ist && ost); ++i){
			ist >> n;
			ost << n << ' ';
		}
		ost << '\n';
	}
}
