export module grammar;

import token_system;
import symbol_table;
import std;

using namespace std;

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
	primary '!'
primary:
	number
	'(' expression ')'
	'-' primary
	'+' primary
	pow '(' expression ',' int ')'
	sqrt '(' expression ')'
number:
	float value
	name
*/

export namespace grammar{
	double statement(Token_stream&, istream&, Symbol_table&);
	double declaration(bool, Token_stream&, istream&, Symbol_table&);
	double expression(Token_stream&, istream&, Symbol_table&);
	double term(Token_stream&, istream&, Symbol_table&);
	double subterm(Token_stream&, istream&, Symbol_table&);
	double primary(Token_stream&, istream&, Symbol_table&);
	
	int safe_int_cast(double);
	double pow(double, double);
	int factorial(double);
}
