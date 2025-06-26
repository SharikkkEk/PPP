//Стартовый код
#include <iostream>
#include <vector>
using namespace std;

string game();

vector<int> moves;

int main(){
	string will = "Yes";
	while (will == "Yes" || will == "yes"){
		cout << game();
		cout << "\nYou wanna play? ";
		cin >> will;
	}
}

int next_value(int value){
	if (moves.size() % 2 == 0)
		return value % 2 + 1;
	else
		return value % 3;
}

string game(){
	cout << "You wanna play? Let's play\n" << "Your move and value: ";

	string result;	
	string user_move;
	int value;
	cin >> user_move >> value;

	moves.push_back(next_value(value));

	switch (moves[moves.size() - 1]){
	case 0:
		if (user_move == "Rock")
			result = "draw";
		else if(user_move == "Paper")
			result = "you win";
		else if(user_move == "Scissors")
			result = "You lose";
		break;
	case 1:
		if (user_move == "Rock")
			result = "You lose";
		else if(user_move == "Paper")
			result = "draw";
		else if(user_move == "Scissors")
			result = "you win";
		break;
	case 2:
		if (user_move == "Rock")
			result = "you win";
		else if(user_move == "Paper")
			result = "You lose";
		else if(user_move == "Scissors")
			result = "draw";
		break;
	}
	
	return result;
}