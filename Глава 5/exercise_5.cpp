#include <iostream>

/*
expression:
	term
	expression "|" term
term:
	subterm
	term "^" subterm
subterm:
	unary
	subterm "&" unary
unary:
	primary
	"!" unary
	"~" unary
primary:
	number
	"(" expression ")"
number:
	bit
	number bit
bit:
	"0"
	"1"
*/

int main(){
}
