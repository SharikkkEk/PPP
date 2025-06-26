//Стартовый код
#include <iostream>
#include <vector>
using namespace std;

vector<string> sort(vector<string> v){
	for(int x = 0; x < v.size()-1; ++x){
		for(int y = 0; y < v.size()-x-1; ++y){
			if (v[y] > v[y+1]){
				string temp = v[y];
				v[y] = v[y+1];
				v[y+1] = temp;
			}
		}
	}
	
	return v;
}

int main(){
	cout << "Please write your words: ";
	vector<string> words;
	for(string word; cin >> word;)
		words.push_back(word);
	
	if (words.size() == 0)
		throw runtime_error("You must write words");
	
	words = sort(words);	

	for (int i = 0; i < words.size(); ++i){
		if (i == 0||words[i-1] != words[i])
			cout << words[i] << " ";
	}
}
