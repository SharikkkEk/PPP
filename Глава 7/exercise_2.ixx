export module print_vector;

import std;

export std::string print_vector(const std::vector<int>& vector){
	std::string str = "{ ";
	for (int x: vector){
		if (x == 0){
			str += "0, ";
			continue;
		}
		if (x < 0) str += '-';

		x = std::abs(x);
		std::string num_str;
		while (x > 0){
			num_str += (x % 10 + '0');
			x /= 10;
		}

		char num_size = num_str.size() - 1; // Last index

		for (char i = num_size; i > num_size/2; --i){
			char tmp = num_str[i];
			num_str[i] = num_str[num_size-i];
			num_str[num_size-i] = tmp;
		}
		
		str += num_str + ", ";
	}

	str[str.size()-1] = '}';
	str[str.size()-2] = ' ';

	return str;
}

export void print_vector_inplace(const std::vector<int>& vector, std::string& str){
	str += "{ ";
	for (int x: vector){
		if (x == 0){
			str += "0, ";
			continue;
		}
		if (x < 0) str += '-';

		x = std::abs(x);
		std::string num_str;
		while (x > 0){
			num_str += (x % 10 + '0');
			x /= 10;
		}

		char num_size = num_str.size() - 1; // Last index

		for (char i = num_size; i > num_size/2; --i){
			char tmp = num_str[i];
			num_str[i] = num_str[num_size-i];
			num_str[num_size-i] = tmp;
		}
		
		str += num_str + ", ";
	}

	str[str.size()-1] = '}';
	str[str.size()-2] = ' ';
}
