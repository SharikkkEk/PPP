//Начальный код
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

constexpr int conv_k = 48;

bool find(std::vector<int> v, int n) {
	for (int x : v) {
		if (x == n)
			return true;
	}
	return false;
}

std::vector<int> get_vector() { // Возвращает вектор, состоящий из 4 различных цифр, введённых пользователем
	std::vector<int> usr_numbers;
	while (usr_numbers.size() < 4) {
		char n = '0';
		std::cin >> n;
		int number = n - conv_k;
		if (n >= '0' && n <= '9' && !(find(usr_numbers, number)))
			usr_numbers.push_back(number);
		else
			std::cout << "You must enter four diffirent digits\n";
	}
	return usr_numbers;
}

std::vector<int> fill_random() { // Возвращает вектор, состоящий из различных рандомных символов
	std::default_random_engine engine(time(NULL));
	std::uniform_int_distribution<int> dist(0, 9);
	std::vector<int> v;

	while (v.size() < 4) {
		int r_n = dist(engine);
		if (!find(v, r_n))
			v.push_back(r_n);
	}

	return v;
}

int count_bulls_cows(std::vector<int> v_guess, std::vector<int> v_usr) { // подсчитывает кол=во коров и быков
	int cows = 0;
	int bulls = 0;

	for (int i = 0; i < v_guess.size(); ++i) {
		for (int j = 0; j < v_usr.size(); ++j) {
			if (v_guess[i] == v_usr[j]) {
				bulls += i == j; // Инкрементируем кол-во быков, если совпадает место цифры в векторе пользователя и векторе программф
				cows += i != j; // Инкрементируем кол-во коров, если нет
			}
		}
	}

	std::cout << "Cows count: " << cows << " bulls count: " << bulls << "\n";
	return bulls;
}

void game() {
	//std::vector<int> v_guess = fill_random();
	std::vector<int> v_guess{ 1, 2, 3, 4 };
	int bulls = 0;
	while (bulls < 4) {
		std::cout << "Enter 4 different digits ";
		std::vector<int> v_usr_number = get_vector();

		bulls = count_bulls_cows(v_guess, v_usr_number);
	}
	std::cout << "You win!\n";
}

int main() {
	std::cout << "Welcome to 'cows and bulls' game!\n";
	std::string ans = "yes";
	while(ans == "yes") {
		game();
		std::cout << "If you wanna more enter 'yes' ";
		std::cin >> ans;
	}
}