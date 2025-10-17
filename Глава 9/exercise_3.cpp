#include <iostream>
#include <fstream>

bool is_vowel(char ch){
	ch = tolower(ch);
	switch (ch){
	case 97: 
	case 101:
	case 105:
	case 111:
	case 117:
	case 121:
		return true;
	}
	return false;
}


int main(){
	std::string no_vowels;
	std::ifstream file {"3.txt"};
	
	char ch;
	int space_count = 0;
	while (file.get(ch)){
		if (!is_vowel(ch)){
			if (ch == ' '){
				if (space_count == 0){
					no_vowels += ' ';
					space_count++;
				}
			}
			else {
				no_vowels += ch;
				space_count = 0;
			}
		}
	}

	std::ofstream no_vowels_f {"3.txt"};
	no_vowels_f << no_vowels;
}
