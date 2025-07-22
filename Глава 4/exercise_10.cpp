#include <iostream>
#include <vector>

// ===== Forward declaration =====

std::vector<double> get_numbers();
double sum_first_N(const std::vector<double>& v, int count);
void print_diff(const std::vector<double>& numbers);

// ===== Main =====

int main() 
try {
	std::cout << "Please enter the numbers of values you want to sum: ";
	int count = 0; 
	std::cin >> count;
	if (!std::cin || count < 0) // При нецелом вводе дробная часть попадёт в вектор numbers
		throw std::runtime_error("You must enter a positive integer");
	
	std::cout << "Enter your numbers(press '|' to stop): ";
	std::vector<double> numbers = get_numbers();
	std::cout << "Sum of first " << count << ": " << sum_first_N(numbers, count) << "\n";
	print_diff(numbers);
	
}

catch(std::exception& e){
	std::cerr << e.what();
}

// ===== Function definition =====

std::vector<double> get_numbers(){
	std::vector<double> numbers;
	for (double i = 0; std::cin >> i;){
		numbers.push_back(i);
	}
	return numbers;
}

double sum_first_N(const std::vector<double>& v, int count) {
	if (count > v.size())
		throw std::runtime_error("Not enough values to sum the requested amount");

	double sum_N = 0;
	for (int i = 0; i < count; ++i) {
		sum_N += v[i];
	}
	return sum_N;
}

void print_diff(const std::vector<double>& numbers){
	std::vector<double> diff;

	for (int i = 1; i < numbers.size(); ++i)
		diff.push_back(numbers[i] - numbers[i-1]);

	std::cout << "Differences between adjacent values: ";
	for (double x: diff)
		std::cout << x << " ";

	std::cout << '\n';
}
