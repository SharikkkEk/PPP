import std;
using namespace std;

int main() {
	vector<int> a{ 1, 2, 3, 4, 7, 9 };
	cout << sizeof(a) << "\n"; // размер менеджмента в байтах(указатели на конец и начало даты, на конец всей аллоцированной памяти
	cout << a.size() << "\n"; // длина даты

	int c = 2;
	double b = 2.5;

	if (b > c) {
		cout << "Что за хуйня";
	}
}