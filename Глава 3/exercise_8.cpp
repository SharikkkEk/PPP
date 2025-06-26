//Стартовый код
#include <iostream>
#include <vector>
using namespace std;

constexpr int conv_ratio = 48;

int conv(string str);

int main(){
	string str_number1;
	string str_number2;
	char oper;
	
	cin >> str_number1 >> oper >> str_number2;

	int number1 = conv(str_number1);
	int number2 = conv(str_number2);

	switch(oper){
	case '+':
		cout << double{number1} + number2;
	case '-':
		cout << double{number1} - number2;
	case '*':
		cout << double{number1} * number2;
	case '/':
		cout << double{number1} / number2;
	}
}

int conv(string str){
	if (str >= "0" && str <= "9")
		return int(str[0])-conv_ratio;
	else{
		if (str == "zero")
			return 0;
		else if (str == "one")
			return 1;
		else if (str == "two")
			return 2;
		else if (str == "three")
			return 3;
		else if (str == "four")
			return 4;
		else if (str == "five")
			return 5;
		else if (str == "six")
			return 6;
		else if (str == "seven")
			return 7;
		else if (str == "eight")
			return 8;
		else if (str == "nine")
			return 9;
	}
	return -1;
}
