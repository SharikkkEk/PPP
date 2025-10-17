#include <iostream>
#include <fstream>

int space = 0;
int alpha = 0;
int digit = 0;
int xdigit = 0;
int upper = 0;
int lower = 0;
int alnum = 0;
int cntrl = 0;
int punct = 0;
int print = 0;
int graph = 0;

void ch_class(char);

int main(){
	std::ifstream ist {"13.txt"};
	char ch;
	while (ist >> ch)
		ch_class(ch);

	std::cout << "space: " << space << '\n'
		  << "alpha: " << alpha << '\n'
		  << "digit: " << digit << '\n'
		  << "xdigit: " << xdigit << '\n'
		  << "upper: " << upper << '\n'
		  << "lower: " << lower << '\n'
		  << "alnum: " << alnum << '\n'
		  << "cntrl: " << cntrl << '\n'
		  << "punct: " << punct << '\n'
		  << "print: " << print << '\n'
		  << "graph: " << graph;
}

void ch_class(char ch){
	space += bool(isspace(ch));
	alpha += bool(isalpha(ch));
	digit += bool(isdigit(ch));
	xdigit += bool(isxdigit(ch));
	upper += bool(isupper(ch));
	lower += bool(islower(ch));
	alnum += bool(isalnum(ch));
	cntrl += bool(iscntrl(ch));
	punct += bool(ispunct(ch));
	print += bool(isprint(ch));
	graph += bool(isgraph(ch));
}
