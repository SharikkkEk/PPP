#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	vector<int> v;
	for (int i; cin >> i;)
		v.push_back(i);
	sort(v.begin(), v.end());

	int k = 1;
	int mode = v[0];
	int mode_k = 1;
	
	for (int i = 1; i < v.size(); ++i){
		if (v[i-1] == v[i]){
			k+=1;
			if (mode_k < k){
				mode = v[i];
				mode_k = k;
			}
		}
		else{
			k = 1;
		}
	}
	
	cout << mode;
}