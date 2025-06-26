#include <iostream>
using namespace std;

int main(){
	string operation;
	double val1 = -1.0;
	double val2 = -1.0;
	cin >> operation >> val1 >> val2;
	
	if (operation == "+"){
		cout << val1+val2;
	}
	else if(operation == "-"){
		cout << val1-val2;
	}
	else if(operation == "*"){
		cout << val1*val2;
	}
	else if(operation == "/"){
		cout << val1/val2;
	}
}