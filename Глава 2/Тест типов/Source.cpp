import std;
using namespace std;

int main() {
	vector<int> a{ 1, 2, 3, 4, 7, 9 };
	cout << sizeof(a) << "\n"; // ������ ����������� � ������(��������� �� ����� � ������ ����, �� ����� ���� �������������� ������
	cout << a.size() << "\n"; // ����� ����

	int c = 2;
	double b = 2.5;

	if (b > c) {
		cout << "��� �� �����";
	}
}