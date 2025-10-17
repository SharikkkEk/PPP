#include <iostream>
#include <vector>

void print_ch_type(char);

int main(){
	int n = 0;
	std::cin >> n;
	std::vector<std::string> vector;
	vector.reserve(n);

	for (int i = 0; i < n; ++i){
		std::string str;
		std::cin >> str;
		vector.push_back(str);
	}

	for (std::string str : vector){
		std::cout << "String: " << str << '\n';
		std::cout << "Character types:\n";
		for (char ch : str)
			print_ch_type(ch);
	}
}

void print_ch_type(char ch) {
	std::cout << ch << " <- ";
	if (ch == 127)
		std::cout << "control";
	else if (ch >= 123)
		std::cout << "print, graph and punct";
	else if (ch >= 103)
		std::cout << "print, graph, alpha and lower";
	else if (ch >= 97)
		std::cout << "print, graph, alpha, lower and xdigit";
	else if (ch >= 91)
		std::cout << "print, graph and punct";
	else if (ch >= 71)
		std::cout << "print, graph, alpha and upper";
	else if (ch >= 65)
		std::cout << "print, graph, alpha, upper and xdigit";
	else if (ch >= 58)
		std::cout << "print, graph and punct";
	else if (ch >= 48)
		std::cout << "print, graph, digit and xdigit";
	else if (ch >= 33)
		std::cout << "print, graph and punct";
	else if (ch == 32)
		std::cout << "print, space and blank";
	else if (ch >= 14)
		std::cout << "control";
	else if (ch >= 10)
		std::cout << "control and space";
	else if (ch == 9)
		std::cout << "control, space and blank";
	else if (ch >= 0)
		std::cout << "control";
	std::cout << '\n';
}
