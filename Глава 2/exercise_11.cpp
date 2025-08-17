#include <iostream>
#include <map>

int main(){
	int pennie_value[] {1, 5, 10, 25, 50, 100};
	const char* money[] = {"pennie", "nickel", "dime", "quarter", "half dollar", "dollar" };
	std::map<std::string, int> usr_money;
	unsigned short i = 0;
	int sum = 0;
	
	for (const char* str: money){
		std::cout << "How many " << str << "s you have?\n";
		std::cin >> usr_money[str];
	}
	
	for (const char* str: money){
		int& x = usr_money[str];

		if (x != 0){
			std::cout << "You have " << x << " " << str;
			if (x > 0)
				std::cout << "s";
			std::cout << '\n';
		}

		x *= pennie_value[i++];
		sum += x;
	}

	int dollars  = sum / 100;
	int pennies = sum % 100;
	std::cout << "You have " << dollars << (dollars == 1 ? " dollar " : " dollars ") 
		  << pennies << (pennies == 1 ? " pennie" : " pennies") << std::endl;
}
