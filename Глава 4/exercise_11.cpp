//Начальный код
#include <iostream>
#include <vector>

std::vector<int> get_f(int N){
	std::vector<int> f {1, 1};
	for (int i = 0; i < N-2;++i){
		f.push_back(f[i] + f[i+1]);	
	}
	
	return f;
}

int main(){
	int N = 0;
	std::cin >> N;

	std::vector<int> f = get_f(N);
	
	for (int x : f)
		std::cout << x << " ";
	
	int f1 = 1; int f2 = 1; int f3 = 2;
	while(f3 > 0){
		f1 = f2;
		f2 = f3;
		f3 += f1;
	}
	std::cout << "\nLast Fibonacci number that fits in an int is " << f2;
}