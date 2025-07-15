#include <iostream>
#include <vector>

// ===== Forward declaration =====

std::vector<int> decompose(int number);
void print_digits(std::vector<int>& vector, const int& number);

// ===== Main =====

int main(){
	int number = 0;
	std::cin >> number;

	if (!std::cin || number >= 10000)
		throw std::runtime_error("you must enter 1, 2, 3 or 4 digits");

	std::vector<int> digits = decompose(number);
	print_digits(digits, number);
}

// ===== Functions =====

std::vector<int> decompose(int number){
	std::vector<int> vector;

	do {
		vector.push_back(number%10);
		number /= 10;
	} while (number > 0); // do while is needed to handle the "0" case

	return vector;
}

void print_digits(std::vector<int>& vector, const int& number){
	std::cout << number << " is ";
	switch (vector.size()){
	case 4:
		std::cout << vector.back() << " thousand and ";
		vector.pop_back();
		[[fallthrough]];
	case 3:
		std::cout << vector.back() << " hundred and ";
		vector.pop_back();
		[[fallthrough]];
	case 2:
		std::cout << vector.back() << " tens and ";
		vector.pop_back();
		[[fallthrough]];
	case 1:
		std::cout << vector.back() << " ones\n";
		break;
	default:
		break;
	}
}
