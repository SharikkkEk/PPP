#include <iostream>
#include <vector>

void min_max(const std::vector<std::string>& vector, std::string& max, std::string& min){
	max = "";
	min = vector[0];

	for (const std::string& x: vector){
		if (x.size() > max.size())
			max = x;
		else if (x.size() < min.size())
			min = x;
	}
}

void first_last(const std::vector<std::string>& vector, std::string& first, std::string& last){
	first = vector[0];
	last = vector[0];

	for (const std::string x: vector){
		if (x < first){
			first = x;
		}
		else if (x > last){
			last = x;
		}
	}
}

int main(){
	std::vector<std::string> vector {"G", "A", "Z", "ADAs", "FDS"};

	std::string max;
	std::string min;
	std::string first;
	std::string last;

	min_max(vector, max, min);
	first_last(vector, first, last);

	std::cout << max << '\n'
		  << min << '\n'
		  << first << '\n'
		  << last << '\n';
}
