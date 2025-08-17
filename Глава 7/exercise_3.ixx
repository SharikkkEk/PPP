export module fibonacci;

import std;

export void fibonacci(int x, int y, std::vector<int>& vector, int n){
	vector.push_back(x);
	vector.push_back(y);

	for (int i = 2; i < n; ++i)
		vector.push_back(vector[i-1] + vector[i-2]);
}
