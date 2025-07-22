#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>

int main(){
	int rejected = 0;
	int count = 0;
	std::cin >> count;

	std::vector<std::vector<int>> week_values(7);
	std::unordered_map<std::string, std::vector<int>*> week_days = {
		{"monday", &week_values[0]},
		{"mon", &week_values[0]},
		{"tuesday", &week_values[1]},
		{"tue", &week_values[1]},
		{"wednesday", &week_values[2]},
		{"wed", &week_values[2]},
		{"thursday", &week_values[3]},
		{"thur", &week_values[3]},
		{"friday", &week_values[4]},
		{"fri", &week_values[4]},
		{"saturday", &week_values[5]},
		{"satur", &week_values[5]},
		{"sunday", &week_values[6]},
		{"sun", &week_values[6]}
	};

	for(int i = 0; i < count; ++i){
		std::string day;
		int value = 0;
		std::cin >> day >> value;
		std::transform(day.begin(), day.end(), day.begin(), [](char c){return std::tolower(c);});
		if (week_days.find(day) != week_days.end())
			week_days[day]->push_back(value);
		else
			++rejected;
	}

	const char* days_of_week[] = {
		"monday", "tuesday", "wednesday", "thursday",
		"friday", "saturday", "sunday"
	};

	for (std::string day : days_of_week){
		std::cout << day << ":";
		int sum = 0;
		for (int value : *week_days[day]) {
			std::cout << " " << value;
		}
		std::cout << " Sum: " << sum << '\n';
	}
	std::cout << "Rejected count: " << rejected;
}

