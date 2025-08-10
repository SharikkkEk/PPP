// Калькулятор на основе рекурсивного спуска

import std;
import constants;
import utils;

import grammar;
import symbol_table;
import token_system;

using namespace cnst;
using namespace utils;

// ===== Input initialization =====

std::istream& utils::input = std::cin;

// ===== Constants =====

const char help[] = R"(Calculator features:
support for user defined variables and constants
	- for defining variable use "#" key
	example:
	# rad = 0.529
	- for defining constants use "const" key
	example: const tau = 6.283
functions
	- sqrt({value})
	- pow({value}, {power})
	accepts only positive and integer powers
Control:
	";" - marks the end of expression
	example: 2+2; 3+3
	"quit" - quit the calculator
)";

// ===== Auxiliary =====

void calculate(){
	while (input)
	try{
		std::cout << prompt_key;
		Token t = ts.get();

		while (t.kind == print_key || t.kind == help_key){
			if (t.kind == help_key)
				std::cout << help;
			t = ts.get();
		}
		if (t.kind == quit_key)
			break;   

		ts.putback(t); // Кладём токен в поток, чтобы последующий вызов функции смог его получить
		std::cout << result_key << grammar::statement() << '\n'; 
	}
	catch (std::exception& e){
		std::cerr << e.what() << '\n';
		ts.ignore(print_key);
	}
}

// ===== Main =====

int main()
try{
	names.define_const("k", 1000); // Для записи типа 1k, 2kk

	// define_var потому что пользователь, возможно, захочет изменить значение на более, либо менее точное
	names.define_var("pi", 3.1415926535); 
	names.define_var("e", std::exp(1)); // std::exp(1) возвращает значение самой экспоненты

	calculate();
	return 0;
}
catch(std::exception& e){
	std::cerr << e.what();
	return 1;
}
catch(...){
	std::cerr << "exception";
	return 2;
}
