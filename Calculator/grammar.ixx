export module grammar;

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

export namespace grammar{
	double statement();
	double declaration(bool);
	double expression();
	double term();
	double subterm();
	double primary();
	
	int safe_int_cast(double);
	double pow(double, double);
	int factorial(double);
}
