#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

inline void cin_flush(){
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

using vector_size = unsigned long long;

namespace Name_lib{
	// ===== Class declaration =====
	class Name_pairs{
	public:
		void read_names();
		void read_ages();
		void sort();

		const std::vector<int>& get_ages() const;
		const std::vector<std::string>& get_names() const;

		bool operator==(Name_pairs& pair) const;
		bool operator!=(Name_pairs& pair) const;
	private:
		std::vector<std::string> names;
		std::vector<int> ages;
	};

	// ===== Implementation of functions =====
	
	void Name_pairs::read_names(){
		std::cout << "How many names do you want to enter? ";
		int count = 0;
		std::cin >> count;
		if (!std::cin){
			std::cerr << "Input error\n";
			return;
		}
	
		names.reserve(names.size() + count);
		for (int i = 0; i < count; ++i){
			std::string str;
			std::cin >> str;

			if (!std::cin){
				std::cerr << "Input error\n";
				return;
			}
			names.push_back(str);
		}
		ages.reserve(names.size());
	}

	void Name_pairs::read_ages(){
		for (auto i = ages.size(); i < names.size(); ++i){
			std::cout << "Enter the age for " << names[i] << ": ";
			int age = 0;
			std::cin >> age;

			while (!std::cin){
				std::cerr << "Input error\n";
				cin_flush();
				std::cin >> age;
			}
			ages.push_back(age);
		}
	}

	void Name_pairs::sort(){
		std::vector<std::string> copied_names = names;
		std::vector<int> copied_ages = ages;
		std::sort(names.begin(), names.end());

		for (vector_size i = 0; i < ages.size(); ++i){
			vector_size position = 0;
			position = std::find(copied_names.begin(), copied_names.end(), names[i]) - copied_names.begin();
			ages[i] = copied_ages[position];
		}
	}

	const std::vector<int>& Name_pairs::get_ages() const{
		return ages;
	}

	const std::vector<std::string>& Name_pairs::get_names() const{
		return names;
	}
	
	bool Name_pairs::operator==(Name_pairs& pairs) const{
		return this->get_names() == pairs.get_names() && this->get_ages() == pairs.get_ages();
	}

	bool Name_pairs::operator!=(Name_pairs& pairs) const{
		return this->get_names() != pairs.get_names() && this->get_ages() != pairs.get_ages();
	}

	// ===== Global operators =====

	std::ostream& operator<<(std::ostream& os, Name_pairs& pairs){
		for (vector_size i = 0; i < pairs.get_ages().size(); ++i){ 
			os << pairs.get_names()[i] << " " << pairs.get_ages()[i] << "\n";
		}
		return os;
	}
}

int main(){
	Name_lib::Name_pairs pairs{};

	pairs.read_names();
	pairs.read_ages();

	Name_lib::Name_pairs pairs1{};
	pairs1.read_names();
	pairs1.read_ages();

	std::cout << int(pairs1 != pairs);
}
