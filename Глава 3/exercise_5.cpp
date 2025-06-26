//Стартовый код
#include <iostream>
#include <vector>
using namespace std;

int main(){
	string will = "yes";
	while (will == "yes"){
		int low = 1;
		int high = 101;
		bool right = false;
		
		for (int i = 0; i < 7; ++i){
			int gues_number = (low + high)/2;	
			cout << "Is your number " << gues_number << "(write 'yes', 'higher', 'lower')\n";		
			string ans;
				
			while(cin >> ans){
				if (ans == "yes"){
					cout << "I always win\n";
					right = true;
					break;
				}
				else if (ans == "higher"){
					low = gues_number;
					break;
				}
				else if(ans == "lower"){
					high = gues_number;
					break;
				}
				else
					cout << "You must write 'yes', 'higher', 'lower'\n";
			}
			if (right)
				break;
		}
		if (!right)
			cout << "You're kidding\n";
		cout << "Should we continue? (write 'yes' or something else) ";
		cin >> will;
	}
}
