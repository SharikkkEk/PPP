#include <iostream>
using namespace std;

int main(){
	string friend_name_a;
	cout << "Please, enter the name of the person you want to write to: ";
	cin >> friend_name_a;

	cout << "Dear " << friend_name_a << ", \n";
	cout << "How are you? I'm fine. I miss you\n";
	cout << "Did you go to the gym every week and never skip zanyatija?\n";

	cout << "Please, enter your another friend name: ";
	string friend_name_b;
	cin >> friend_name_b;
	cout << "Have you seen " << friend_name_b << " lately?\n";

	int age = -1;
	cout << "Please, enter your friend's age: ";
	cin >> age;
	if (age <= 0 or age >= 110){
		std::cerr << "you're kidding";
		exit(1);
	}
	
	if (age < 12){
		cout << "Next year you will be " << age+1 << "\n"; 
	}
	if (age == 12){
		cout << "Next year you will be able to vote\n";
	}
	if (age > 70){
		cout << "Are you retired?\n";
	}

	cout << "Yours sincerely,\n\nSharik";
}