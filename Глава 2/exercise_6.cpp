#include <iostream>
#include <vector>
using namespace std;

int main(){
	string val1;
	string val2;
	string val3;
	
	cin >> val1 >> val2 >> val3;
	
	if(val1<=val2 and val1<=val3){
		cout << val1 << ", ";
		if (val2 < val3){
			cout << val2 << ", ";
			cout << val3;
		}
		else{
			cout << val3 << ", ";
			cout << val2;
		}
	}
	else if(val2<=val1 and val2<=val3){
		cout << val2 << ", ";
		if (val1 < val3){
			cout << val1 << ", ";
			cout << val3;
		}
		else{
			cout << val3 << ", ";
			cout << val1;
		}
	}
	else if(val3<=val2 and val3<=val1){
		cout << val3 << ", ";
		if (val2 < val1){
			cout << val2 << ", ";
			cout << val1;
		}
		else{
			cout << val1 << ", ";
			cout << val2;
		}
	}
}