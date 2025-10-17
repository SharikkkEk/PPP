#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct Point {
	int x;
	int y;
};

istream& operator>>(istream& ist, Point& p){
	char ch1, ch2, ch3 = 0;
	int x, y = 0;
	ist >> ch1 >> x >> ch2 >> y >> ch3; 
	if (ist.fail()) {
		return ist;
	} else if (ch1 != '(' || ch2 != ',' || ch3 != ')') {
		ist.clear(ios::failbit);
		return ist;
	} 
	p.x = x;
	p.y = y;
	return ist;
}

ostream& operator<<(ostream&, Point p){
	std::cout << '(' << p.x << ',' << p.y << ')';
	return cout;
}

int main(){
	vector<Point> points;
	cout << "Enter points\n";
	for (int i = 0; i < 7; ++i){
		Point a;
		cout << "Point: ";
		cin >> a;
		if (!(cin.fail())) 
			points.push_back(a);
	}
	
	ofstream ost {"MyData.txt"};
	
	for (auto x : points)
		ost << x << '\n';
}
