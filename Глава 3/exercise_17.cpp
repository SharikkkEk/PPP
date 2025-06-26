//Стартовый код
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main(){
	double a = 0;
	double b = 0;
	double c = 0;
	
	cin >> a >> b >> c;

	double D = b*b - 4*a*c;
	
	if(D == 0)
		cout << -b/(2*a);
	else if(D > 0)
		cout << "x1 = " << (-b + sqrt(D))/(2*a) << " x2 = " << (-b - sqrt(D))/(2*a);
	else
		cout << "There's no solution";
}