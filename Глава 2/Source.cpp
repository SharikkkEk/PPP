import std;
using namespace std;

int main() { 
	cout << "Enter your age and name, please: ";
	double age;
	string firstName;
	cin >> age >> firstName;
	cout << "Hello, " << firstName << " (age " << age * 12 << ")\n";
}