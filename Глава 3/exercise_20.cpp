//Стартовый код
#include <iostream>
#include <vector>
using namespace std;

bool find_bool(string elem, vector<string> v){
	for (string x: v){
		if (elem == x)
			return true;
	}
	return false;
}

int main(){
	vector<string> names;
	vector<int> scores;
	
	string name;
	int score=0;
	
	while((name != "NoName" || score != 0) && cin >> name >> score){
		if (find_bool(name, names))
			break;
		names.push_back(name);
		scores.push_back(score);
	}
	
	names.pop_back();

	cout << "Find your values!\n";

	int find_value;

	while (cin >> find_value){
		bool not_finded = true;
		for (int i = 0; i < names.size(); ++i){
			if (find_value == scores[i]){
				cout << names[i] << "\n";
				not_finded = false;
			}
		}
		if (not_finded)
			cout << "score not found\n";
	}
}