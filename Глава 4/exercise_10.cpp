#include <iostream>
#include <vector>

double sum_first_N(std::vector<double> v, int count) {
	if (count > v.size())
		throw std::runtime_error("Count of values you enter must be >= than count of values you wanna sum");
	double sum_N = 0;
	for (int i = 0; i < count; ++i) {
		if (sum_N + v[i] > 2147483647)
			throw std::runtime_error("Sum cannot be represented as an int");
		sum_N += v[i];
	}
	return sum_N;
}

int main() {
	double N_d = 0; // Принимаем дабл, чтобы учитывать возможный ввод нецелого числа
	std::cout << "Please enter the numbers of values you want to sum: ";
	std::cin >> N_d;
	int N = N_d;
	if (!std::cin || N <= 0 || N < N_d)
		throw std::runtime_error("You must enter a positive integer");

	std::vector<double> numbers;
	for (double i = 0; std::cin >> i;)
		numbers.push_back(i);
	if (numbers.size() == 0)
		throw std::runtime_error("You entered no values");
	std::cout << sum_first_N(numbers, N) << "\n";
	
	
	std::vector<double> diff;
	for (int i = 1; i < numbers.size(); ++i){
		diff.push_back(numbers[i] - numbers[i-1]);
	}

	for (double x: diff)
		std::cout << x << " ";
}