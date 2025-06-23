import std;
using namespace std;

int main() {
	string previous;
	string current;
	int n = 1;
	while (cin >> current) { // Можно будет вводить до того момента, пока не встретится ctrl Z(^Z) или символ неподходящего типа
		if (previous == current) {
			cout << current << " was repeated on position " << n << "\n";
		}
		previous = current;
		n++;
	}
}