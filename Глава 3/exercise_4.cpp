//Стартовый код
#include <iostream>
#include <vector>
using namespace std;

int main(){
	cout << "Enter your distances: ";
	vector<double> distances;
	for (double i; cin >> i;)
		distances.push_back(i);
	
	double sum = 0;
	double max = -100000;
	double min = 1000000;
	for (double x: distances){
		sum += x;
		if (max < x)
			max = x;
		if (min > x)
			min = x;
	}
	
	if (distances.size() == 0)
		cout << "You must enter distances";
	else
		cout << "Total distance: " << sum << " smallest distance: " << min << " greatest distance: " << max << " mean distance: " << sum/distances.size();
}
