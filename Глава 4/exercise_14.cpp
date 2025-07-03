//Стартовый код
#include <iostream>
#include <vector>

int get_index(std::vector<std::vector<std::string>>* week_days, std::string s){
	for (int i = 0; i < week_days->size();++i){
		auto week_ptr = week_days->begin()+i;
		for (auto j = week_ptr->begin(); j<week_ptr->end();++j){
			if (*j == s)
				return i;
		}
	}
	return -1;
}

void fill_week(std::vector<std::vector<std::string>>* week){
	week->push_back({"Monday", "monday", "mon", "Mon"});
	week->push_back({"Tuesday", "tuesday"});
	week->push_back({"Wednesday", "wednesday"});
	week->push_back({"Thursday", "thursday"});
	week->push_back({"Friday", "friday"});
	week->push_back({"Saturday", "saturday"});
	week->push_back({"Sunday", "sunday"});
}

int main(){
	std::vector<std::vector<int>> week_values;
	for (int i = 0; i < 7; ++i) 
		week_values.push_back({});
	std::vector<std::vector<std::string>> week_days;
	fill_week(&week_days);
	int count = 0;

	std::string week;
	int number = 0;

	while(std::cin >> week && std::cin >> number){
		int index = get_index(&week_days, week);
		if (index > -1){
			week_values[index].push_back(number);
		}
		else{
			++count;
		}
	}

	for (int i = 0; i < 7; ++i){
		std::cout << week_days[i][0] << " ";
		int sum = 0;
		for (int j : week_values[i]){
			std::cout << j << " ";
			sum += j;
		}
		std::cout << "sum " << sum << "\n";
	}

	std::cout << "Rejected count " << count;
}