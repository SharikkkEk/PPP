import std;
using namespace std;

int main() {
	string previous;
	string current;
	int n = 1;
	while (cin >> current) { // ����� ����� ������� �� ���� �������, ���� �� ���������� ctrl Z(^Z) ��� ������ ������������� ����
		if (previous == current) {
			cout << current << " was repeated on position " << n << "\n";
		}
		previous = current;
		n++;
	}
}