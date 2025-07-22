#include <iostream>
#include <vector>
using namespace std;

int main(){
	double n = 0;
	std::cin >> n;

	if (n < 1){

		std::cout << "I can't calculate such a logarithm";
		return 1;
	}

	// P {n - вещественные число и n >= 1}

	int count = 0;
	long double two = 1;

	// Q1 {count = 0 и two = 1}

	while(two < n){
		two *= 2;
		++count;
	}

	/*
	Доказательство того, что цикл while имеет конечное число итераций:
	1. Объявления
	   Пусть count = k, n - вещественное число, P(k) : two >= n после k-го прохода цикла 


	1. Объявления
	   Пусть count = k, P(k) : 2^k = two после k-го прохода цикла

	   
	*/

	// Q2 {2^count = two и 2^(count-1) < n <= 2^(count)}

	std::cout << count;

	// Q {count = ceil(log(2)n)}
}
