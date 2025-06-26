#include <iostream>
using namespace std;

int main(){
	cout << "Enter your values: ";
	double val1 = -1.0;
	double val2 = -1.0;
	cin >> val1 >> val2;

	if(val1 > val2){
		cout << "Smaller: " << val2;
		cout << "\nLarger: " << val1;
		cout << "\nDiff: " << val1-val2;
		cout << "\nRatio: " << val1/val2;
	}
	else{
		cout << "Smaller: " << val1;
		cout << "\nLarger: " << val2;
		cout << "\nDiff: " << val2-val1;
		cout << "\nRatio: " << val2/val1;
	}
	cout << "\nSum: " << val1+val2;
	cout << "\nProduct: " << val1*val2;
}