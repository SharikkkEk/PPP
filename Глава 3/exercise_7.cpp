//Стартовый код
#include <iostream>
#include <vector>
using namespace std;

bool number_speller(){
	vector<string> numbers = {"null", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	int number = 0;
	cout << "Please, enter your number: ";
	cin >> number;
	
	if (number < 10 && number > 0)
		cout << numbers[number];
	else
		cout << "I don't know that number";
	
	string will;
	cout << "\nWanna more? ";
	cin >> will;
	if(will == "Yes" || will == "yes"){
		return true;
	}
	else{
		return false;
	}
}

int main(){
	bool will = number_speller();
	while(will){
		will = number_speller();
	}

	cout << "\n:(";
}