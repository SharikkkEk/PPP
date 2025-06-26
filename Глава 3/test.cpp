
//Стартовый код
#include <iostream>
#include <vector>
using namespace std;

int main(){
	cout << "Please write your words: ";
	vector<string> words;
	for(string word; cin >> word;)
		words.push_back(word);
	
	if (words.size() == 0)
		throw runtime_error("You must write words");
	
	vector<string> disliked_words = {"Broccoli", "Pypa", "hui"};
	
	for (string word : words){
		bool is_dis = false;
		for (string dis_word : disliked_words){
			if(word == dis_word){
				is_dis = true;
				break;
			}
		}
		if (is_dis)
			cout << "BLEEP ";
		else
			cout << word << " ";
	}
}