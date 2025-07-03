//Начальный код
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

constexpr int conv_k = 48;

int count_bulls_cows(std::vector<int> v_guess, std::vector<int> v_usr) {
	int cows = 0;
	int bulls = 0;

	for (int i = 0; i < v_guess.size(); ++i) {
		for (int j = 0; j < v_usr.size(); ++j) {
			if (v_guess[i] == v_usr[j]) {
				bulls += i == j;
				cows += i != j;
			}
		}
	}

	std::cout << "Cows count: " << cows << " bulls count: " << bulls << "\n";
	return bulls;
}

bool check_repeated(std::vector<int> v) {
	std::sort(v.begin(), v.end());
	for (int i = 1; i < v.size(); ++i) {
		if (v[i] == v[i - 1])
			return true;
	}
	return false;
}

std::vector<int> vectorization(int n) {
	if (!(n >= 1000 && 10000 > n))
		throw std::runtime_error("number must be 1000<=n<=9999");

	std::vector<int> v(4);
	for (int i = 0; i < 4; ++i) {
		v[3 - i] = n % 10; // Разворачиваем число обратно
		n /= 10;
	}
	return v;
}

void game();

bool find(std::vector<int> v, int n){
	for (int x: v){
		if (x == n)
			return true;
	}
	return false;
}

std::vector<int> fill_random(){
	std::default_random_engine engine;
	std::uniform_int_distribution<int> dist(0, 9);
	std::vector<int> v;
	
	while (v.size() < 4){
		int r_n = dist(engine);
		if (!find(v, r_n))
			v.push_back(r_n);
	}
	
	return v;
}

int main(){
	std::vector<int> usr_numbers;
	for (int i = 0; i < 4; ++i){
		char n = '0';
		std::cin >> n;
		if (n >= '0' && n <= '9')
			usr_numbers.push_back(n-conv_k);
	}
	if (usr_numbers.size() < 4){
		throw std::runtime_error("you must enter four diffirent digits");
	}
}

void game() {
	std::vector<int> v_guess = fill_random();
	int bulls = 0;
	while (bulls < 4){
		int usr_number = 0;
		std::cin >> usr_number;
		std::vector<int> v_usr_number = vectorization(usr_number);

		if (check_repeated(v_usr_number)) {
			throw std::runtime_error("number must not having repeated digits");
		}

		bulls = count_bulls_cows(v_guess, v_usr_number);
	}
	std::cout << "You win!\n";
}