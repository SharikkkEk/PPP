//Начальный код
#include <iostream>

double ktoc(double k){
	if (k < 0){
		throw std::runtime_error("Too low temperature");		
	}
	double c = k - 273.15;
	return c;
}

double ctok(double c){
	if (c < -273.15){
		throw std::runtime_error("Too low temperature");
	}
	double k = c + 273.15;
	return k;
}

int main(){
	double k = 0;
	std::cin >> k;
	double c = ktoc(k);
	std::cout << c << "\n";
}