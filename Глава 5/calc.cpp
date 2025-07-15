#include <iostream>

// ===== Grammar =====

/*
expression:
	term
	expression '+' term
	expression '-' term
term:
	subterm
	term '*' subterm
	term '/' subterm
subterm:
	primary
	'!' primary
primary:
	number
	'(' expression ')'
number:
	float value
*/

// ===== Forward declaration =====

class Token;
class Token_stream;

double expression();
double term();
double subterm();
double primary();

int factorial(double value);

// ===== Token system =====

class Token{
public:
	char kind;
	double value;
	Token(char k) :kind{k}, value{0.0} {}
	Token(char k, double v) :kind{k}, value{v} {}
};

class Token_stream{
public:
	Token get();
	void putback(Token t);
	Token_stream();
private:
	bool full = false;
	Token buffer;
};

// ===== Token_stream methods =====

Token Token_stream::get(){
	if (full){
		full = false;
		return buffer;
	}
	char ch;
	std::cin >> ch;
	switch (ch){
	case 'q': case ';': case '!':
	case '+': case '-': case '*': case '/':
	case '(': case ')': case '{': case '}': 
		return Token(ch);	
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{	std::cin.putback(ch);
		double val;
		std::cin >> val;
		return Token('8', val);
	}
	default:
		throw std::runtime_error("Bad Token");
	}
}

void Token_stream::putback(Token t){
	if (full)
		throw std::runtime_error("buffer is full");
	full = true;
	buffer = t;
}

Token_stream::Token_stream(): full{false}, buffer{0} {}

// ===== Global state =====

Token_stream ts;

// ===== Grammar rules =====

double primary(){
	Token t = ts.get();
	switch (t.kind){
	case '(': case '{':
	{	double d = expression();
		t = ts.get();
		if (t.kind != ')' && t.kind != '}')
			throw std::runtime_error("')' expected");
		return d;
	}
	case '8':
		return t.value;
	default:
		throw std::runtime_error("primary expected");
	}
}

double subterm(){
	double left = primary();
	Token t = ts.get();
	switch(t.kind){
	case '!':
		return factorial(left);
	default:
		ts.putback(t);
		return left;
	}
}

double term(){
	double left = subterm();
	Token t = ts.get();
	while (true){
		switch(t.kind){
		case '*':
			left *= subterm();
			t = ts.get();
			break;
		case '/':
		{
			double d = subterm();
			if (d == 0) 
				throw std::runtime_error("Divide by zero");
			left /= d;
			t = ts.get();
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
	Token t = ts.get();
	while (true){
		switch(t.kind){
		case '+':
			left += term(); 
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

// ===== Auxiliary ======

int factorial(double val){
	int res = 1;
	int int_val = val; // Narrowing conversion 
	if (val < 0)
		throw std::runtime_error("the factorial of a negative number does not exist");
	for (int i = 2; i<=int_val; ++i){
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

// ===== Main =====

int main()
try{
	double val = 0;
	std::cout << "> ";
	while (std::cin){
		Token t = ts.get();
		if (t.kind == 'q')
			break;
		if (t.kind == ';'){
			std::cout << "= " << val << '\n';
			std::cout << "> ";
		}
		else
			ts.putback(t);
		val = expression(); //Измени положение этой строчки. Из-за неё неправильная ошибка выходит
	}
}
catch(std::exception& e){
	std::cerr << e.what();
	return 1;
}
catch(...){
	std::cerr << "exception";
	return 2;
}
