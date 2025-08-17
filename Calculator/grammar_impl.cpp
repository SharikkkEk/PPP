module grammar;

import std;
import constants;
import utils;

import symbol_table;
import token_system;

using namespace utils;
using namespace std;
using namespace cnst;
using namespace grammar;

double grammar::primary(Token_stream& ts, istream& input, Symbol_table& names){
	Token t = ts.get();

	switch (t.kind){
	case '(': case '{':
	{	double d = expression(ts, input, names); // Внутри скобок должно быть выражение
		t = ts.get();
		if (t.kind != ')' && t.kind != '}')
			throw runtime_error("')' or '}' expected");
		return d;
	}
	case number_key:
		return t.value;
	case sqrt_key:
	{ 	t = ts.get();
		if (t.kind != '(')
			throw runtime_error("'(' expected");

		double d = expression(ts, input, names);
		if (d < 0)
			throw runtime_error("square root of negative number is not defined");

		t = ts.get();
		if (t.kind != ')')
			throw runtime_error("')' expected");

		return sqrt(d);
	}
	case pow_key:
	{	t = ts.get();
		if (t.kind != '(')
			throw runtime_error("'(' expected");

		double d = expression(ts, input, names);

		t = ts.get();
		if (t.kind != ',')
			throw runtime_error("',' expected");

		double power = expression(ts, input, names);

		t = ts.get();
		if (t.kind != ')')
			throw runtime_error("')' expected");

		return pow(d, power);
	}
	case '-':
		return - primary(ts, input, names);
	case '+':
		return primary(ts, input, names);
	case name_key:
		return names.get_value(t.name);
	default:
		ts.putback(t);
		throw runtime_error("primary expected");
	}
}

double grammar::subterm(Token_stream& ts, istream& input, Symbol_table& names){
	double left = primary(ts, input, names);
	Token t = ts.get();

	switch (t.kind){
	case '!':
		return factorial(left);
	default:
		ts.putback(t);
		return left;
	}
}

double grammar::term(Token_stream& ts, istream& input, Symbol_table& names){
	double left = subterm(ts, input, names);
	
	while (true){
		Token t = ts.get();
		switch(t.kind){
		case '*':
			left *= subterm(ts, input, names);
			break;
		case '/':
		{
			double d = subterm(ts, input, names);
			if (d == 0) 
				throw runtime_error("Divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			double d = subterm(ts, input, names);
			if (d == 0)
				throw runtime_error("Modulo by zero");
			left = fmod(left, d); // Остаток от деления для нецелых чисел; x%y=x-y*int(x/y)
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double grammar::expression(Token_stream& ts, istream& input, Symbol_table& names){
	double left = term(ts, input, names);

	while (true){
		Token t = ts.get();
		switch(t.kind){
		case '+':
			left += term(ts, input, names); 
			break;
		case '-':
			left -= term(ts, input, names);
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

double grammar::declaration(bool is_const, Token_stream& ts, istream& input, Symbol_table& names){
	Token t = ts.get();
	if (t.kind != name_key)
		throw runtime_error("name expected in declaration");
	
	Token t2 = ts.get();
	if (t2.kind != '=')
		throw runtime_error("'=' missing in declaration of " + t.name + " or forbidden character has been entered");
	
	double d = expression(ts, input, names);
	if (is_const)
		names.define_const(t.name, d);
	else 
		names.define_var(t.name, d);
	return d;
}

double grammar::statement(Token_stream& ts, istream& input, Symbol_table& names){
	Token t = ts.get();

	switch (t.kind){
	case decl_key:
		return declaration(false, ts, input, names);
	case const_key:
		return declaration(true, ts, input, names);
	case name_key: 
	// Если в вводе встречено имя, то это либо вычисление какого-то выражения, либо присвоение значения переменной
	{	char ch = input_wo_ws(input);

		if (ch == '=')
			return names.set_value(t.name, expression(ts, input, names));

		ts.putback(t);
		input.unget(); 
		return expression(ts, input, names);
	}
	default:
		ts.putback(t); 
		return expression(ts, input, names);
	}
}

// ===== Auxiliary ======

int grammar::safe_int_cast(double d){
	int i = static_cast<int>(d);
	if (i != d)
		throw std::runtime_error("narrowing conversion from double to int");
	return i;
}

double grammar::pow(double value, double d_power){ // Принимаем степень в double, чтобы проверить, целое ли это число
	int power = safe_int_cast(d_power);
	double res = 1;

	for (int i = 0; i < power; ++i)
		res *= value;
	for (int i = 0; i > power; --i)
		res /= value;

	return res;
}

int grammar::factorial(double val){
	int res = 1;
	int int_val = safe_int_cast(val);
	
	if (val < 0)
		throw std::runtime_error("the factorial of a negative number does not exist");

	for (int i = 2; i<=int_val; ++i){ // Начинается с 2 потому, что 0! = 1! = 1
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

