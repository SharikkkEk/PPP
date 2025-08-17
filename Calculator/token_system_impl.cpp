module token_system;

import std;
import utils;
import constants;

using namespace cnst;
using namespace std;
using namespace utils;

// ===== Token constructors =====

Token::Token(char ch) :kind{ch}, value{0.0} {}
Token::Token(char ch, double val) :kind{ch}, value{val} {}
Token::Token(char ch, string n) :kind{ch}, name{n} {}

// ===== Token_stream constructor =====

Token_stream::Token_stream(istream& in): full{false}, buffer{0}, input{in} {}

// ===== Token_stream methods =====

Token Token_stream::get(){
	if (full){
		full = false;
		return buffer;
	}

	char ch = input_wo_ws(input);

	switch (ch){
	case '\n':
		return Token(print_key);

	case print_key: case decl_key: 
	case '!': case '%': case '+': case '-': case '*': case '/':
	case '(': case ')': case '{': case '}': case '=': case ',':
		return Token(ch);	

	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{	input.unget(); // Кладём цифру обратно
		double val;
		input >> val; // Считываем число полностью
		
		input.get(ch);
		while (ch == 'k'){
			val *= 1000;
			input.get(ch);
		}
		input.unget();

		return Token(number_key, val);
	}

	default:
		if (isalpha(ch) || ch == '_'){ 
			string s;
			s += ch;

			while(input.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))  // В имени переменной могут быть только цифры и буквы
				s += ch;
			input.unget(); // Последний прочитанный символ не цифра и не буква - кладём в поток обратно, чтобы другие функции смогли его прочитать

			if (s == "sqrt")
				return Token(sqrt_key);
			if (s == "pow")
				return Token(pow_key);
			if (s == "const")
				return Token(const_key);
			if (s == "quit")
				return Token(quit_key);
			if (s == "help")
				return Token(help_key);

			return Token{name_key, s};
		}

		throw runtime_error("Bad token");
	}
}

void Token_stream::putback(Token t){
	if (full)
		throw runtime_error("buffer is full");
	full = true;
	buffer = t;
}

void Token_stream::ignore(char c){
	/*
	В одной строчкe могут встретиться выражения с ошибкой и без.
	Для того, чтобы выражение без ошибки было расчитано, нам нужно пропустить выражение с ошибкой
	Все выражения заканчиваются на ';'. Следовательно, если мы встретили ошибку - просто пропускаем ввод до первой ';'.
	Функция может пропустить ввод не только до ';', но и до любого символа
	*/
	if (full && c==buffer.kind){
		full = false;
		return;
	}
	full = false; // Очищаем буфер, потому что после ошибки он может содержать устаревший токен

	char ch = 0;
	while (input.get(ch)){
		if (ch == c || ch == '\n')  
			return;
	}
}
