//Начальный код
#include "PPP.h"


int sum(int x, int y) {
	return [&] {return x + y;}();
}

int main() {
	cout << sum(1, 2);
}