#include <iostream>
#include <vector>
#include <algorithm>

// ===== Class =====

class Name_value{
public:
	int value = 0;
	std::string Name;
	Name_value(int x, std::string y);
};

Name_value::Name_value(int x, std::string y): value{x}, Name{y} {}

// ===== Main =====

int main()
try {
	std::vector<Name_value> pairs;
	std::string name;
	int val = 0;
	
	while (std::cin >> name >> val && (name != "NoName" || val != 0)){
		auto cond {[&](Name_value target) -> bool {
			return target.Name == name; }
		};
		auto is_finded = std::find_if(begin(pairs), end(pairs), cond);
		if (is_finded != end(pairs)) // Проверка того, что до этого имени не было в векторе
			throw std::runtime_error("names must be unique");
		pairs.push_back(Name_value{val, name});
	}

	if (!std::cin) {
		throw std::runtime_error("input error");
	}

	std::cout << "Find your values!" << std::endl;
	
	int target_int = 0;
	while (std::cin >> target_int){
		auto cond {[&](Name_value target) -> bool {
			return target.value == target_int; }
		};
		auto value_finded = std::find_if(begin(pairs), end(pairs), cond);
		if (value_finded == end(pairs))
			std::cout << "Value not finded" << std::endl;
		else
			std::cout << value_finded->Name << std::endl;
	}

	return 0;
}
catch (std::exception& e){
	std::cout << e.what() << std::endl;

	return 1;
}
