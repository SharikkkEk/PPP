#include "iostream"
using namespace std;

string gram_correction(int value){
	if(value > 1){
		return "s";
	}
	else{
		return "";
	}
}

int main(){
	int pennies = 0;
	int nickels = 0;
	int dimes = 0;
	int quarters = 0;
	int half_dollars = 0;
	int dollars = 0;

	cout << "How many pennies do you have? ";
	cin >> pennies;
	cout << "How many nickels do you have? ";
	cin >> nickels;
	cout << "How many dimes do you have? ";
	cin >> dimes;
	cout << "How many quarters do you have? ";
	cin >> quarters;
	cout << "How many half dollars do you have? ";
	cin >> half_dollars;
	cout << "How many dollars do you have? ";
	cin >> dollars;
	
	if (pennies != 0){
		cout << "You have " << pennies << " pennie" << gram_correction(pennies) << ".\n";
	}
	if (nickels != 0){
		cout << "You have " << nickels << " nickel" << gram_correction(nickels) << ".\n";
	}
	if (dimes != 0){
		cout << "You have " << dimes << " dime" << gram_correction(dimes) << ".\n";
	}
	if (quarters != 0){
		cout << "You have " << quarters << " quarter" << gram_correction(quarters) << ".\n";
	}
	if (half_dollars  != 0){
		cout << "You have " << half_dollars << " half dollar" << gram_correction(half_dollars) << ".\n";
	}
	if (dollars  != 0){
		cout << "You have " << dollars  << " dollar" << gram_correction(dollars) << ".\n";
	}
	
	int sum_dollars = (pennies+nickels*5+dimes*10+quarters*25+half_dollars*50+dollars*100)/100;
	int sum_cents = (pennies+nickels*5+dimes*10+quarters*25+half_dollars*50+dollars*100) - sum_dollars*100;
	
	cout << "The value of all of your coins is " << sum_dollars << " dollars and " << sum_cents << " cents.";
}

