#include <iostream>
#include <cctype>
#include <sstream>

int nt_size = 3; // size of "n't" word

void to_low(std::string&);
std::string parse(std::string&, bool&);

int main(){
        std::string line;
        std::getline(std::cin, line);
	std::istringstream ist {line};
	bool in_quotes = false;
	
	char ch = 0;
	while (ist.get(ch)){
		if (ch != ' '){
			ist.unget();
			std::string str;
			ist >> str;
			std::cout << parse(str, in_quotes);
		}
		else
			std::cout << ch;
	}
}

std::string parse(std::string& str, bool& in_quotes){
	to_low(str);
	for (char ch : str)
		if (ch == '"')
			in_quotes = !in_quotes;

	if (str == "can't")
		return "cannot";

	if (str.size() == 1){
		if (ispunct(str[0]) && !in_quotes)
			str[0] = ' ';
		return str;
	}
	// ГОВНОКОД НАДО ИСПРАВИТЬ

	auto it = str.end()-1;
	while (ispunct(*it) && it > str.begin()){
		--it;
	}

	size_t search_pos = it - str.begin();
	search_pos -= nt_size;


	size_t pos = str.find("n't", search_pos);
	if (pos != str.npos){
		str.erase(str.begin() + pos, ++it);
		str.insert(pos, " not");
	}

	return str;
}

void to_low(std::string& str){
	for (char& ch : str)
		ch = tolower(ch);
}
