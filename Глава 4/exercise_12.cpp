#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <chrono>

// ===== Forward declaration =====

void game();
void fill_random(std::vector<int>& vector);
void get_digits(std::vector<int>& vector);
bool check_repeated(std::vector<int> v);
int count_bulls_cows(std::vector<int> v_guess, std::vector<int> v_usr); 

// ===== Game =====

void game() {
	std::vector<int> v_guess;
	fill_random(v_guess);

	int bulls = 0;

	while (bulls < 4){
		std::vector<int> v_usr;
		get_digits(v_usr);

		if (check_repeated(v_usr)) {
			throw std::runtime_error("number must not having repeated digits");
		}

		bulls = count_bulls_cows(v_guess, v_usr);
	}
	std::cout << "You win!\n";
}

// ===== Main =====

int main(){
	char answer = 'y';
	std::cout << "Welcome to the bulls and cows game!\n";
	while (answer == 'y'){
		game();
		std::cout << "Write 'y' if you wanna continue ";
		std::cin >> answer;
	}
}

// ===== Auxiliary functions =====

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

void fill_random(std::vector<int>& vector){
	std::default_random_engine engine(std::time(nullptr));
	std::uniform_int_distribution<int> dist(0, 9);
	
	while (vector.size() < 4){
		int random_number = dist(engine);
		if (std::find(begin(vector), end(vector), random_number) == end(vector))
			vector.push_back(random_number);
	}
}

void get_digits(std::vector<int>& vector){
	char c;
	for (int i = 0; i < 4; ++i){
		std::cin >> c;
		if (!std::cin)
			throw std::runtime_error("input error");
		if (c >= '0' && c <= '9')
			vector.push_back(c - '0');
		else
			throw std::runtime_error("you must enter only digits");
	}
}
