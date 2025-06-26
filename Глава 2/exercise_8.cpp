//Определяет, чётное ли число
#include <iostream>
using namespace std;

int main(){
	int value = -1;
	cout << "Please, enter your value: ";
	cin >> value;
	
	if (value % 2 == 0){
		cout << "The value " << value << " is even";
	}
	else{
		cout << "The value " << value << " is odd";
	}
}