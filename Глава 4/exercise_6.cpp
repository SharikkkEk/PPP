//Начальный код
#include <iostream>

double ctof(double c){
	if(c < -273.15)
		throw std::runtime_error("Too low temp");
	double f = c*9/5 + 32;
	return f;
}

int main(){
	
}