// Калькулятор на основе рекурсивного спуска
#include <iostream>
#include <cmath>
#include <map>

// ===== Constant Inizialization =====

constexpr char print = ';';
constexpr char quit = 'q';
constexpr char prompt = '>';
constexpr char result = '=';

constexpr char number = '8'; // 8 - произвольный символ для обозначения типа number у токена
constexpr char name = 'a';
constexpr char let = 'L';
const std::string declkey = "let";

constexpr char pow_ch = '^';
constexpr char sqrt_ch = '<';

// ===== Grammar =====

/*
calculation:
	statement
	print
	quit
statement:
	expression
	declaration
	assignment
print:
	';'
quit:
	'q'
declaration:
	"let" name '=' expression
assignment:
	name '=' expression
expression:
	term
	expression '+' term
	expression '-' term
term:
	primary
	term '*' primary
	term '/' primary
	term % primary
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

double declaration();
double assignment();
double expression();
double term();
double primary();

void calculate();
int factorial(double value);
void clean_up_mess();
int safe_int_cast(double d); // Преобразование с проверкой на сужение
double pow(double value, double d_power); // Возведение в степень

bool is_declared(std::string var);
double define_name(std::string var, double val);

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

	char ch;
	std::cin >> ch;

	switch (ch){
	case quit: case print:
	case '!': case '%': case '+': case '-': case '*': case '/': case ',':
	case '(': case ')': case '{': case '}': case '=':
		return Token(ch);	
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{	std::cin.putback(ch); // Кладём цифру обратно
		double val;
		std::cin >> val; // Считываем число полностью
		return Token(number, val);
	}
	default:
		if (std::isalpha(ch)){ // Имя может начинаться только с буквы
			std::string s;
			s += ch;

			while(std::cin.get(ch) && (std::isalpha(ch) || std::isdigit(ch)))  // В имени переменной могут быть только цифры и буквы
				s += ch;

			std::cin.putback(ch); 
			// Последний прочитанный символ не цифра и не буква - кладём в поток обратно, чтобы другие функции смогли его прочитать
			if (s == declkey) 
				return Token{let};
			if (s == "sqrt")
				return Token(sqrt_ch);
			if (s == "pow")
				return Token(pow_ch);
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
	Для того, чтобы второе было расчитано, нам нужно пропустить первое. 
	Все выражения заканчиваются на ';'. Следовательно, если мы встретили ошибку - просто пропускаем ввод до первой ';'.
	*/
	if (full && c==buffer.kind){
		full = false;
		return;
	}
	full = false; // Очищаем буфер, потому что после ошибки он может содержать устаревший токен

	char ch = 0;
	while (std::cin >> ch){
		if (ch == c)
			return;
	}
}

Token_stream::Token_stream(): full{false}, buffer{0} {}

// ===== Token stream initialization =====

Token_stream ts;

// ===== Variable system =====

std::map<std::string, double> var_table;

double set_value(std::string s, double d){
	auto it = var_table.find(s);

	if (it != var_table.end()) // find() возвращает end(), если элемент не был найден
		it->second = d;
		return d;

	throw std::runtime_error("trying to write undefined variable " + s);
}

double get_value(std::string s){
	auto it = var_table.find(s);

	if (it != var_table.end())
		return it->second;

	throw std::runtime_error("trying to read undefined variable " + s);
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
		char ch;
		std::cin >> ch;
		
		if (ch == '!')
			return factorial(t.value);

		std::cin.putback(ch);
		return t.value;
	case sqrt_ch:
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
	case pow_ch:
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
	case 'a':
		return get_value(t.name);
	default:
		throw std::runtime_error("primary expected");
	}
}

double term(){
	double left = primary();
	
	while (true){
		Token t = ts.get();
		switch(t.kind){
		case '*':
			left *= primary();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) 
				throw std::runtime_error("Divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			double d = primary();
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

double declaration(){
	Token t = ts.get();
	if (t.kind != name)
		throw std::runtime_error("name expected in declaration");
	
	Token t2 = ts.get();
	if (t2.kind != '=')
		throw std::runtime_error("= missing in declaration of " + t.name);
	
	double d = expression();
	define_name(t.name, d);
	return d;
}

double statement(){
	Token t = ts.get();

	switch (t.kind){
	case let:
		return declaration();
	case name:
		char ch;
		std::cin >> ch;

		if (ch != '='){
			ts.putback(t);
			std::cin.putback(ch); // Кладём токен в поток, чтобы последующий вызов expression смог его получить
			return expression();
		}

		return set_value(t.name, expression());
	default:
		ts.putback(t); 
		return expression();
	}
}

// ===== Auxiliary ======

void calculate(){
	while (std::cin)
	try{
		std::cout << prompt;
		Token t = ts.get();

		if (t.kind == print)
			t = ts.get();
		if (t.kind == quit)
			break;   

		ts.putback(t);
		std::cout << result << statement() << '\n'; 
	}
	catch (std::exception& e){
		std::cerr << e.what() << '\n';
		clean_up_mess();
	}
}

void clean_up_mess(){
	ts.ignore(print);
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


int safe_int_cast(double d){
	int i = static_cast<int>(d);
	if (static_cast<int>(d) != d)
		throw std::runtime_error("narrowing conversion");
	return i;
}

double pow(double value, double d_power){ // Принимаем степень в double, чтобы проверить, целое ли это число
	int power = safe_int_cast(d_power);
	double res = 1;
	for (int i = 0; i < power; ++i)
		res *= value;
	for (int i = 0; i > power; --i)
		res /= value;
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

// ===== Auxiliary variable functions =====

double define_name(std::string var, double val){
	if (is_declared(var))
		throw std::runtime_error(var + " declared twice");
	var_table[var] = val;
	return val;
}

bool is_declared(std::string var){
	auto it = var_table.find(var);

	if (it == var_table.end())
		return false;
	return true;
}

// ===== Main =====

int main()
try{
	define_name("k", 1000);
	define_name("pi", M_PI);
	define_name("e", std::exp(1)); // std::exp(1) возвращает значение самой экспоненты

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
