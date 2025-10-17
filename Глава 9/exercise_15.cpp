#include <fstream>
#include <vector>
#include <algorithm>

int main(){
	std::ifstream ist {"numbers.txt"};
	std::vector<int> values;
	int n = 0;
	while (ist){
		ist >> n;
		values.push_back(n);
	}
	std::sort(values.begin(), values.end());
	
	std::ofstream ost {"15.txt"};
	int number = 1;
	while (number < values.size()){
		int counter = 1;
		while (values[number-1] == values[number]){
			number++;
			counter++;
		}
		ost << values[number] << ' ' << counter << '\n';
		number++;
	}
}
