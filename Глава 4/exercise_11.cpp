#include <iostream>
#include <vector>

int main(){
	int N = 0;
	std::cin >> N;
	
	int prev = 0; int current = 0; int next = 1;
	
	for (int i = 0; i < N; ++i){
		std::cout << current << ' ';
		prev = current;
		current = next;
		next += prev;
	}

	while (next > 0){
		prev = current;
		current = next;
		next += prev;
	}

	std::cout << "\nLast fibonacci number that fits in int: " << current;
}
