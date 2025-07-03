//Начальный код
#include <iostream>
#include <vector>

int sum_first_N(std::vector<int> v, int count) {
	if (count > v.size())
		throw std::runtime_error("Count of values you enter must be >= than count of values you wanna sum");
	int sum_N = 0;
	for (int i = 0; i < count; ++i) {
		sum_N += v[i];
		if (sum_N < 0)
			throw std::runtime_error("Sum cannot be represented as an int");
	}
	return sum_N;
}

int main() {
	int N = 0;
	std::cout << "Please enter the numbers of values you want to sum: ";
	std::cin >> N;
	if (!std::cin || N <= 0)
		throw std::runtime_error("You must enter a positive integer");
	std::vector<int> numbers;
	for (int i = 0; std::cin >> i;)
		numbers.push_back(i);
	if (numbers.size() == 0)
		throw std::runtime_error("You entered a non integer value or no values");
	try {
		std::cout << sum_first_N(numbers, N);
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
	}
}