#include "iostream"
using namespace std;

bool number_speller(){
	string number;
	cout << "Please, enter your number: ";
	cin >> number;

	if (number == "zero"){
		cout << 0;
	}
	else if (number == "one"){
		cout << 1;
	}
	else if (number == "two"){
		cout << 2;
	}
	else if (number == "three"){
		cout << 3;
	}
	else if (number == "four"){
		cout << 4;
	}
	else{
		cout << "I'm so stupid. I don't know that number";
	}

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

