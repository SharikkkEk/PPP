//Стартовый код
#include <iostream>
#include <vector>
using namespace std;

vector<bool> numbers;

int main(){
	vector<int> primes;
	int n;
	cin >> n;	

	for (int i = 0; i < n; ++i)
		numbers.push_back(true);
	
	for (int i = 2; i < n; ++i){
		if(numbers[i]){
			for(int mp = 1; i*mp < n; ++mp)
				numbers[i*mp] = false;
			primes.push_back(i);
		}
	}

	for (int x: primes)
		cout << x << " ";
}