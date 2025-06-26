//Стартовый код
#include <iostream>
#include <vector>
using namespace std;

vector<double> sort(vector<double> v){
	for(int x = 0; x < v.size()-1; ++x){
		for(int y = 0; y < v.size()-x-1; ++y){
			bool cond = v[y] > v[y+1];
			if (cond){
				double temp = v[y];
				v[y] = v[y+1];
				v[y+1] = temp;
			}
		}
	}
	return v;
}

int main(){
	vector <double> temps;
	
	for(double i; cin >> i; )
		temps.push_back(i);

	temps = sort(temps);
	
	if (temps.size()/2.0 > temps.size()/2)
		cout << temps[temps.size()/2];
	else
		cout << (temps[temps.size()/2-1] + temps[temps.size()/2])/2;
}
