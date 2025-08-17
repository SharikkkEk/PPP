export module token_system;

import std;
using namespace std;

// ===== Token system =====

export class Token{
public:
	char kind;
	double value;
	string name;
	Token(char ch); // Конструктор для токенов, содержащих символы
	Token(char ch, double val); // Конструктор для токенов, содержащих числа
	Token(char ch, string n); // Конструктор для токенов, содержащих переменные
};

export class Token_stream{
public:
	Token get();
	void putback(Token);
	void ignore(char);
	Token_stream(istream&);
	istream& input;
private:
	bool full = false;
	Token buffer;
	/*
	Нам необходимо место лишь для одного токена потому что:
	Если в буфере есть токен, то функция при вызове get() обязана взять его оттуда. Буфер становится пустым
	Если его тип не подойдёт функции, то она положит токен обратно. В буфере после этого будет только один токен
	*/
};
