#include <iostream>
using namespace std;

int main(){
	double money;
	char valuta;
	cout << "Please enter your money followed by 'y'(yen), 'k'(kroner) or 'p'(pounds) ";
	cin >> money >> valuta;
	
	switch(valuta){
	case 'y':
		cout << money * 0.01 << "$";
		break;
	case 'k':
		cout << money * 0.10 << "$";
		break;
	case 'p':
		cout << money * 2 << "$";
		break;
	default:
		cout << "I don't know";
		break;
	}
}