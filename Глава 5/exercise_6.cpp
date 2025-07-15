#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <chrono>
#include <unordered_map>


// ===== Forward declaration =====

void game();
void fill_random(std::unordered_map<char, unsigned short>& letters);
void get_letters(std::unordered_map<char, unsigned short>& letters);
int count_bulls_cows(std::unordered_map<char, unsigned short>& letters_guess, std::unordered_map<char, unsigned short>& letters_usr); 

// ===== Game =====

// В этой функции описана структура игры

void game() {
	std::unordered_map<char, unsigned short> letters_guess;
	fill_random(letters_guess);

	int bulls = 0;

	while (bulls < 4){
		std::unordered_map<char, unsigned short> letters_usr;
		get_letters(letters_usr);
		bulls = count_bulls_cows(letters_guess, letters_usr);
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

int count_bulls_cows(std::unordered_map<char, unsigned short>& letters_guess, std::unordered_map<char, unsigned short>& letters_usr) {
	int cows = 0;
	int bulls = 0;
	
	for (auto it = letters_usr.begin(); it != letters_usr.end(); ++it){ 
		auto founded_letter = letters_guess.find(it->first);
		if (founded_letter != letters_guess.end()){ 
			if (letters_usr[it->first] == letters_guess[it->first]) // Получаем позицию элемента в обоих словарях
				++bulls;
			else
				++cows;
		}
	}

	std::cout << "Cows count: " << cows << " bulls count: " << bulls << "\n";
	return bulls;
}

void fill_random(std::unordered_map<char, unsigned short>& letters) {
	std::default_random_engine engine(std::time(nullptr));
	std::uniform_int_distribution<int> dist(65, 90);
 	for (int i = 0; i < 4; ++i){
		while (letters.size() < i){
			int random_letter = dist(engine);
			letters[random_letter] = i;
		}
	}
}

void get_letters(std::unordered_map<char, unsigned short>& letters){
	char c;
	for (int i = 0; i < 4; ++i){
		std::cin >> c;
		if (!std::cin)
			throw std::runtime_error("input error");
		if (c >= 'A' && c <= 'Z')
			letters[c] = i;
		else
			throw std::runtime_error("you must enter only letters");
	}
	if (letters.size() < 4)
		throw std::runtime_error("you must enter 4 different letters");
}
