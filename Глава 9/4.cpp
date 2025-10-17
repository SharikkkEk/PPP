// This code get number in hex, dec, oct in form 0x345 and converts it to a dec
#include <iostream>
#include <fstream>
#include <utility>
#include <ios>
#include <vector>
#include <iomanip>

enum class type {
	hex, oct, dec
};

type get_type();
int get_number(type t);

auto get_values() -> std::vector<std::pair<int, type>>;
void print_values(std::vector<std::pair<int, type>> vector);

int main(){
	std::vector<std::pair<int, type>> values;
	values = get_values();
	print_values(values);
}

auto get_values() -> std::vector<std::pair<int, type>> {
	std::vector<std::pair<int, type>> vector;
	
	while (true) {
		type t = get_type();
		int n = get_number(t);
		if (std::cin.fail())
			break;
		vector.push_back({n, t});
	}

	return vector;
}

void print_values(std::vector<std::pair<int, type>> vector) {
	for (auto x : vector) {
		switch (x.second) {
		case type::hex:
		{	std::ostringstream num;
			num << std::hex << x.first;
			size_t size = num.str().size();
			std::cout << std::hex 
			          << std::setw(9-size) << "0x" << x.first
			       	  << std::setw(15) << " hexadecimal";
			break;
		}
		case type::oct:
		{	std::ostringstream num;
			num << std::oct << x.first;
			size_t size = num.str().size();

			std::cout << std::oct 
			          << std::setw(9-size) << '0' << x.first
				  << std::setw(15) << " octal";
			break;
		}
		case type::dec:
		{	std::ostringstream num;
			num << std::dec << x.first;
			size_t size = num.str().size();

			std::cout << std::dec  
			          << std::setw(9) << x.first
				  << std::setw(15) << " decimal";
			break;
		}
		}

		std::cout << std::setw(15) << "converts to "
		       	  << std::setw(6) << std::dec << x.first
			  << std::setw(10) << " decimal\n";
	}
}

type get_type() {
	char ch;
	std::cin >> ch;
	if (ch != '0'){
		std::cin.putback(ch);
		return type::dec;
	}
	std::cin >> ch;
	if (ch == 'x')
		return type::hex;
	else{
		std::cin.putback(ch);
		return type::oct;
	}
}

int get_number(type t) {
	switch (t) {
	case type::hex:
		std::cin >> std::hex;
		break;
	case type::oct:
		std::cin >> std::oct;
		break;
	case type::dec:
		std::cin >> std::dec;
		break;
	}

	int number = 0;
	std::cin >> number;
	return number;
}
