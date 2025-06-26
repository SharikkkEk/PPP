#include <iostream>
#include <vector>
#include <ranges>

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
	vector<double>	temps;
	for (double tmp; cin >> tmp;){
		temps.push_back(tmp);
	}	

	if (temps.size() == 0)
		throw runtime_error("no temps has been written");
	
	double sum = 0;
	for (double tmp:temps){
		sum += tmp;
	}
	cout << "Average temperature is " << sum/temps.size() << "\n";
	
	temps = sort(temps);
	cout << "Median temperature is " << temps[temps.size()/2];
}
