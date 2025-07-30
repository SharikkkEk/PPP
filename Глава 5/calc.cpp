// Калькулятор на основе рекурсивного спуска с переменными

#include <iostream>
#include <cmath>
#include <map>

// ===== Input stream =====

std::istream& input = std::cin;

// ===== Constant Inizialization =====

constexpr char print = ';';
constexpr char quit = 'q';
constexpr char prompt = '>';
constexpr char result = '=';

constexpr char number = '8'; // 8 - произвольный символ для обозначения типа number у токена
constexpr char name = 'a';
constexpr char decl_key = '#';
constexpr char const_key = 'c';
constexpr char help_key = 'h';

constexpr char pow_key = '^';
constexpr char sqrt_key = '<';

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
// ===== Grammar =====

/*
calculation:
	statement
	print
	quit
	calculation ';' calculation
statement:
	expression
	declaration
	assignment
print:
	';'
quit:
	'q'
declaration:
	'#' name '=' expression
assignment:
	name '=' expression
expression:
	term
	expression '+' term
	expression '-' term
term:
	subterm
	term '*' subterm
	term '/' subterm
	term '%' subterm
subterm:
	primary
	subterm '!'
primary:
	number
	'(' expression ')'
	'-' primary
	'+' primary
	primary '!'
	pow '(' expression ',' int ')'
	sqrt '(' expression ')'
number:
	float value
	name
*/

// ===== Forward declaration =====

class Token;
class Token_stream;

void calculate();
double declaration(bool is_const);
double assignment();
double expression();
double term();
double subterm();
double primary();

int factorial(double value);
int safe_int_cast(double d); // Преобразование с проверкой на сужение
double pow(double value, double d_power); // Возведение в степень

char input_wo_ws(); // Получить символ из потока ввода, пропуская пробелы
void clean_up_mess();

class Symbol_table;

// ===== Token system =====

class Token{
public:
	char kind;
	double value;
	std::string name;
	Token(char ch); // Конструктор для токенов, содержащих символы
	Token(char ch, double val); // Конструктор для токенов, содержащих числа
	Token(char ch, std::string n); // Конструктор для токенов, содержащих переменные
};

class Token_stream{
public:
	Token get();
	void putback(Token t);
	void ignore(char c);
	Token_stream();
private:
	bool full = false;
	Token buffer;
	/*
	Нам необходимо место лишь для одного токена потому что:
	Если в буфере есть токен, то функция при вызове get() обязана взять его оттуда. Буфер становится пустым
	Если его тип не подойдёт функции, то она положит токен обратно. В буфере после этого будет только один токен
	*/
};

// ===== Token constructors =====

Token::Token(char ch) :kind{ch}, value{0.0} {}
Token::Token(char ch, double val) :kind{ch}, value{val} {}
Token::Token(char ch, std::string n) :kind{ch}, name{n} {}

// ===== Token_stream methods =====

Token Token_stream::get(){
	if (full){
		full = false;
		return buffer;
	}

	char ch = input_wo_ws();

	switch (ch){
	case '\n':
		return Token(print);
	case print: case decl_key: 
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

		return Token(number, val);
	}
	default:
		if (std::isalpha(ch) || ch == '_'){ 
			std::string s;
			s += ch;

			while(input.get(ch) && (std::isalpha(ch) || std::isdigit(ch) || ch == '_'))  // В имени переменной могут быть только цифры и буквы
				s += ch;

			input.unget(); // Последний прочитанный символ не цифра и не буква - кладём в поток обратно, чтобы другие функции смогли его прочитать
			if (s == "sqrt")
				return Token(sqrt_key);
			if (s == "pow")
				return Token(pow_key);
			if (s == "const")
				return Token(const_key);
			if (s == "quit")
				return Token(quit);
			if (s == "help")
				return Token(help_key);
			return Token{name, s};
		}

		throw std::runtime_error("Bad token");
	}
}

void Token_stream::putback(Token t){
	if (full)
		throw std::runtime_error("buffer is full");
	full = true;
	buffer = t;
}

void Token_stream::ignore(char c){
	/*
	В одной строчкe могут встретиться выражения с ошибкой и без.
	Для того, чтобы выражение без ошибки было расчитано, нам нужно пропустить ошибочное.
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

Token_stream::Token_stream(): full{false}, buffer{0} {}

Token_stream ts;

// ===== Variable system =====

class Symbol_table{
private:
	std::map<std::string, double> var_table;
	std::map<std::string, double> const_table;
public:
	double set_value(std::string s, double d);
	double get_value(std::string s);
	double define_var(std::string var, double val);
	double define_const(std::string s, double val);
	bool is_declared(std::string var);
};

Symbol_table names;

// ===== Variable system functions definition =====

double Symbol_table::set_value(std::string s, double d){
	auto it = var_table.find(s);

	if (it != var_table.end()){
		it->second = d;
		return d;
	}

	throw std::runtime_error("trying to write undefined variable " + s);
}

double Symbol_table::get_value(std::string s){
	auto it = var_table.find(s);

	if (it != var_table.end())
		return it->second;

	it = const_table.find(s);
	if (it != const_table.end())
		return it->second;

	throw std::runtime_error("trying to read undefined name " + s);
}
	
double Symbol_table::define_var(std::string var, double val){ // Может быть, стоит объединить с define_const
	if (is_declared(var))
		throw std::runtime_error(var + " declared twice");
	var_table[var] = val;
	return val;
}
	
double Symbol_table::define_const(std::string s, double val){
	if (is_declared(s))
		throw std::runtime_error(s + " declared twice");
	const_table[s] = val;
	return val;
}
	
bool Symbol_table::is_declared(std::string var){
	auto it = var_table.find(var);
	if (it != var_table.end())
		return true;
	it = const_table.find(var);
	if (it != const_table.end())
		return true;

	return false;
}

// ===== Grammar rules =====

double primary(){
	Token t = ts.get();

	switch (t.kind){
	case '(': case '{':
	{	double d = expression(); // Внутри скобок должно быть выражение
		t = ts.get();
		if (t.kind != ')' && t.kind != '}')
			throw std::runtime_error("')' or '}' expected");
		return d;
	}
	case number:
		return t.value;
	case sqrt_key:
	{ 	t = ts.get();
		if (t.kind != '(')
			throw std::runtime_error("'(' expected");

		double d = expression();
		if (d < 0)
			throw std::runtime_error("square root of negative number is not defined");

		t = ts.get();
		if (t.kind != ')')
			throw std::runtime_error("')' expected");

		return sqrt(d);
	}
	case pow_key:
	{	t = ts.get();
		if (t.kind != '(')
			throw std::runtime_error("'(' expected");

		double d = expression();

		t = ts.get();
		if (t.kind != ',')
			throw std::runtime_error("',' expected");

		double power = expression();

		t = ts.get();
		if (t.kind != ')')
			throw std::runtime_error("')' expected");

		return pow(d, power);
	}
	case '-':
		return - primary();
	case '+':
		return primary();
	case name:
		return names.get_value(t.name);
	default:
		ts.putback(t);
		throw std::runtime_error("primary expected");
	}
}

double subterm(){
	double left = primary();
	Token t = ts.get();
	while (t.kind == '!'){
		left = factorial(left);
		t = ts.get();
	}

	ts.putback(t);
	return left;
}

double term(){
	double left = subterm();
	
	while (true){
		Token t = ts.get();
		switch(t.kind){
		case '*':
			left *= subterm();
			break;
		case '/':
		{
			double d = subterm();
			if (d == 0) 
				throw std::runtime_error("Divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			double d = subterm();
			if (d == 0)
				throw std::runtime_error("Modulo by zero");
			left = std::fmod(left, d); // Остаток от деления для нецелых чисел; x%y=x-y*int(x/y)
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double expression(){
	double left = term();

	while (true){
		Token t = ts.get();
		switch(t.kind){
		case '+':
			left += term(); 
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

double declaration(bool is_const){
	Token t = ts.get();
	if (t.kind != name)
		throw std::runtime_error("name expected in declaration");
	
	Token t2 = ts.get();
	if (t2.kind != '=')
		throw std::runtime_error("'=' missing in declaration of " + t.name + " or forbidden character has been entered");
	
	double d = expression();
	if (is_const)
		names.define_const(t.name, d);
	else 
		names.define_var(t.name, d);
	return d;
}

double statement(){
	Token t = ts.get();

	switch (t.kind){
	case decl_key:
		return declaration(false);
	case const_key:
		return declaration(true);
	case name: 
	// Если в вводе встречено имя, то это либо вычисление какого-то выражения, либо присвоение значения переменной
	{	char ch = input_wo_ws();

		if (ch == '=')
			return names.set_value(t.name, expression());

		ts.putback(t);
		input.unget(); 
		return expression();
	}
	default:
		ts.putback(t); 
		return expression();
	}
}

// ===== Auxiliary ======

void calculate(){
	while (input)
	try{
		std::cout << prompt;
		Token t = ts.get();

		while (t.kind == print || t.kind == help_key){
			if (t.kind == help_key)
				std::cout << help;
			t = ts.get();
		}
		if (t.kind == quit)
			break;   

		ts.putback(t); // Кладём токен в поток, чтобы последующий вызов функции смог его получить
		std::cout << result << statement() << '\n'; 
	}
	catch (std::exception& e){
		std::cerr << e.what() << '\n';
		clean_up_mess();
	}
}

int safe_int_cast(double d){
	int i = static_cast<int>(d);
	if (static_cast<int>(d) != d)
		throw std::runtime_error("narrowing conversion from double to int");
	return i;
}

void clean_up_mess(){
	ts.ignore(print);
}

char input_wo_ws(){
	char ch;

	do { // Пропускаем пробелы
		input.get(ch);
	} while (ch == ' '); 

	return ch;
}

int factorial(double val){
	int res = 1;

	if (val < 0)
		throw std::runtime_error("the factorial of a negative number does not exist");

	for (int i = 2; i<=val; ++i){ // Начинается с 2 потому, что 0! = 1! = 1
		res *= i;
	}
	return res;
}

/* ===== Formal verification =====

Пусть n = floor(val), где n неотрицательное целое число и floor(val) - целая часть val

0. Определим предикат
   Пусть P(n): res = n! после завершения цикла

1. Базовые случаи
   Для n = 0: цикл не запустится => res = 1 = 0!
   Для n = 1: цикл не запустится => res = 1 = 1!
   Для n = 2: res = 2 * 1 = 2!

2. Индуктивный шаг
   Предположим, что для некоторого k>=0 после завершения цикла res = k! => P(k) - верно
   Тогда для k+1 после завершения цикла res = k! * (k+1) = (k+1)! => P(k+1) - верно

3. Заключение
   Итак, импликация P(k) => P(k+1) верна для всех k>=0. Следовательно, согласно принципу математической индукции, P(n) верен для всех неотрицательных целых n
*/

double pow(double value, double d_power){ // Принимаем степень в double, чтобы проверить, целое ли это число
	int power = safe_int_cast(d_power);
	double res = 1;
	for (int i = 0; i < power; ++i)
		res *= value;
	for (int i = 0; i > power; --i)
		res /= value;
	return res;
}

// ===== Main =====

int main()
try{
	names.define_const("k", 1000);
	names.define_const("pi", M_PI); // M_PI = 3.14.....
	names.define_const("e", std::exp(1)); // std::exp(1) возвращает значение самой экспоненты

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
