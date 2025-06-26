import std;
using namespace std;

vector<double> sort(vector<double> v) {
	for (int x = 0; x < v.size()-1; ++x) {
		for (int y = 0; y < v.size()-x-1; ++y) {
			if (v[y] > v[y+1]) {
				double temp = v[y];
				v[y] = v[y+1];
				v[y+1] = temp;
			}
		}
	}
	return v;
}

int main() {
	constexpr double cm = 100;
	constexpr double in = cm/2.54;
	constexpr double ft = in/12;

	double smallest = 100000;
	double largest = -100000;
	double number = -1;
	vector<double> numbers;
	string unit;

	while (cin >> number >> unit) {
		if (unit == "cm")
			number /= cm;
		else if (unit == "in")
			number /= in;
		else if (unit == "ft")
			number /= ft;
		else if (unit != "m") {
			cout << "illegal unit\n";
			continue;
		}
		if (number > largest){
			cout << "the largest so far\n";
			largest = number;
		}
		if (number < smallest) {
			cout << "the smallest so far\n";
			smallest = number;
		}
		numbers.push_back(number);
	}

	if (numbers.size() > 0) {
		numbers = sort(numbers);
		double sum = 0;
		for (double i : numbers)
			sum += i;
		cout << "The largest: " << largest << "m the smallest: " << smallest << "m sum: " << sum << "m count: " << numbers.size();
	}
}
