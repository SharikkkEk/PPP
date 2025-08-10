export module utils;

import std;

export namespace utils{
	extern std::istream& input;

	char input_wo_ws(){
		char ch;
	
		do { // Пропускаем пробелы
			input.get(ch);
		} while (ch == ' '); 
	
		return ch;
	}
}
