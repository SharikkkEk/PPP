export module reverse;

import std;

export std::vector<int> reverse(const std::vector<int>& vector){
	std::vector<int> re_vector(vector.size(), 0);

	size_t last_index = vector.size()-1;

	for (int i = 0; i < vector.size(); ++i){
		re_vector[i] = vector[last_index-i];
	}

	return re_vector;
}

export void inplace_reverse(std::vector<int>& vector){
	size_t last_index = vector.size()-1;

	for (int i = 0; i < vector.size()/2; ++i){
		std::swap(vector[i], vector[last_index-i]);
	}
}
