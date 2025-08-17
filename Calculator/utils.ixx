export module utils;

import std;

export namespace utils{
	char input_wo_ws(std::istream& input){
		char ch;
	
		do { // Пропускаем пробелы
			input.get(ch);
		} while (ch == ' '); 
	
		return ch;
	}
}
