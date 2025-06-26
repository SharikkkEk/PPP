//Стартовый код
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool define_prime(int number){
	for (int i = 2; i < sqrt(number)+1;++i){
		if (number % i == 0)
			return false;
	}
	return true;
}

int main(){
	vector<int> primes = {2};
	
	for (int i = 2; i < 100; ++i){
		if (define_prime(i))
			primes.push_back(i);
	}

	vector<int> primes1;

	for (int i = 2; i < 100; ++i){
		bool is_prime = true;
		for(int x: primes){
			if (x >= i)
				break;
			if (i % x == 0){
				is_prime = false;
			}
		}
		if (is_prime)
			primes1.push_back(i);
	}

	for(int x : primes)
		cout << x << " ";
	cout << "\n";
	for(int x : primes1)
		cout << x << " ";
}
