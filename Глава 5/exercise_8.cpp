#include <iostream>

// ===== Forward declaration =====

void choice(char answer, int a, int b);
int P(int a, int b); // Permutations
int C(int a, int b); // Combinations
int factorial(int val); 

// ===== Main =====

int main() {
	std::cin.sync_with_stdio(false); // Нужно для того, чтобы иметь доступ к буферу std::cin
	while (true){
		std::cout << "Enter 2 postive integer numbers, where first >= second or 'q' for quit\n";
		char q;
		std::cin >> q;

		if (q == 'q')
			break;
		else
			std::cin.putback(q);

		int a = 0;
		int b = 0;
		std::cin >> a >> b;
		if (!std::cin || (a < b) || (a < 0)){
			std::cout << "ALERT" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			continue;
		}

		std::cout << "What do you want to calculate: Permutations or Combinations? Write 'P' or 'C' respectively\n";

		char answer;
		std::cin >> answer;

		choice(answer, a, b);
	}
}

// ===== Function definition =====

void choice(char answer, int a, int b){
	switch(answer){
	case 'P':
		std::cout << P(a, b) << '\n';
		break;
	case 'C':
		std::cout << C(a, b) << '\n';
		break;
	default:
		std::cout << "I don't know that operation\n";
		break;
	}
}

int P(int a, int b){
	long long int res = 1;
	for (int i = a; i > a-b; --i)
		res *= i;
	return res;
}

int C(int a, int b){
	return P(a, b)/factorial(b);
}


int factorial(int val){
	int res = 1;
	for (int i = 2; i<=val; ++i){
		res *= i;
	}
	return res;
}


