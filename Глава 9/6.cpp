#include <iostream>
#include <cctype>

int main(){
	std::string str;
	std::getline(std::cin, str);
	bool in_quotes = false;

	for (char& ch: str){
		if (ch == '"')
			in_quotes = !in_quotes;
		else if (ispunct(ch) && !in_quotes)
			ch = ' ';
	}
	std::cout << str;
}
