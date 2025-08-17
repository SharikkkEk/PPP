export module reverse_str;

import std;

export std::vector<std::string> reverse_str(std::vector<std::string> vector){
	std::vector<std::string> re_vector(vector.size());
	size_t last_index = vector.size()-1;

	for (int i = 0; i < vector.size(); ++i){
		re_vector[i] = vector[last_index-i];
	}
	
	return re_vector;
}
