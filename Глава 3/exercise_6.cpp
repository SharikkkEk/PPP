//Стартовый код
#include <iostream>
#include <vector>
using namespace std;

int main(){
	double operand1 = -1;
	double operand2 = -1;
	char oper = '+';
	
	cin >> operand1 >> oper >> operand2;
	
	string operandStr;
	double expRes = -2;
	
	switch(oper){
	case '+':
		operandStr = "sum";
		expRes = operand1 + operand2;
		break;
	case '-':
		operandStr = "substract";
		expRes = operand1 - operand2;
		break;
	case '*':
		operandStr = "multiply";
		expRes = operand1 * operand2;
		break;
	case '/':
		operandStr = "divide";
		expRes = operand1 / operand2;
		break;
	}
	
	cout << "The " << operandStr << " of " << operand1 << " and " << operand2 << " is " << expRes;
}
