//Стартовый код
#include <iostream>
#include <vector>

int fibonacci(int count){
	if (count <= 0)
		return -1;
	if (count < 3)
		return 1;
	int f1 = 1;
	int f2 = 1;
	int f3 = f1+f2;
	int current_count = 3;
	
	while (current_count < count){
		f1 = f2;
		f2 = f3;
		f3 += f1;
		++current_count;
	}
	
	if (f3 > 0)
		return f3;
	return -1
}

int main(){
	int n;
	std::cin >> n;
	std::cout << fibonacci(n);
}