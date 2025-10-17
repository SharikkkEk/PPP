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
size_t number_length(std::pair<int, type>);

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
		{	size_t size = number_length(x);

			std::cout << std::hex 
			          << std::setw(6-size) << "0x" << x.first
			       	  << std::setw(12) << " hexadecimal";
			break;
		}
		case type::oct:
		{	size_t size = number_length(x);

			std::cout << std::oct 
			          << std::setw(6-size) << '0' << x.first
				  << std::setw(12) << " octal";
			break;
		}
		case type::dec:
		{	size_t size = number_length(x);

			std::cout << std::dec  
			          << std::setw(6) << x.first
				  << std::setw(12) << " decimal";
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

size_t number_length(std::pair<int, type> x){
	std::ostringstream number;
	switch (x.second){
	case type::hex:
		number << std::hex;
		break;
	case type::oct:
		number << std::oct;
		break;
	case type::dec:
		number << std::dec;
		break;
	}
	number << x.first;
	return number.str().size();
}
