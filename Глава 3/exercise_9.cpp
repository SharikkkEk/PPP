//Стартовый код
#include <iostream>
#include <vector>
using namespace std;


int main(){
	int count = 1;
	double two = 1;
	
	while(count < 64){
		cout << count << " " << two << "\n";
		two *= 2;
		++count;
	}
}