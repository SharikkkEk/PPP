#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

inline void cin_flush(){
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

namespace name_lib{

	// ===== Class declaration =====

	class Name_pairs{
	public:
		void read_names();
		void read_ages();
		void sort();
		const auto& vector() const { return pairs; }

		bool operator==(const Name_pairs&) const;
		bool operator!=(const Name_pairs&) const;
	private:
		class Name_pair;
		std::vector<Name_pair> pairs;
		size_t counter = 0; // Индекс последней пары с определённым age
	};

	// ===== Implementation of functions =====
	
	void Name_pairs::read_names(){
		int count = read_int("How many names do you want to enter? ");
	
		pairs.reserve(pairs.size() + count);
		for (int i = 0; i < count; ++i){
			std::string str;
			std::cin >> str;
			pairs.push_back(Name_pair{str});
		}
	}

	void Name_pairs::read_ages(){
		for (size_t i = counter; i < pairs.size(); ++i){
			int age = read_int("Enter the age for " + pairs[i].Name() + ": ");
			
			pairs[i].set_age(age);
		}
		counter = pairs.size();
	}

	void Name_pairs::sort(){
		std::sort(pairs.begin(), pairs.end(), [] (const Name_pair &a, const Name_pair &b){
			return a.Name() < b.Name();
		});
	}

	bool Name_pairs::operator==(const Name_pairs& cmp) const{
		return this->vector() == cmp.vector();
	}

	bool Name_pairs::operator!=(const Name_pairs& cmp) const{
		return this->vector() != cmp.vector();
	}

	int Name_pairs::read_int(const std::string& str) {
		int num {};
		std::cout << str;
		std::cin >> num;
		
		if (std::cin.eof()) return 0;

		while (!std::cin){
			std::cout << "INPUT ERROR!\n";
			cin_flush();
			std::cin >> num;
		}
		return num;
	}

	class Name_pairs::Name_pair{
		public:
			int Age() const { return age; }
			std::string Name() const { return name; }

			void set_age(int n) { age = n; }
			void set_name(const std::string& str) { name = str; }

			Name_pair(const std::string& str) : name{str}, age{0} {}

			bool operator==(const Name_pair &a) const { return this->age == a.age && this->name == a.name; }
			bool operator!=(const Name_pair &a) const { return this->age != a.age && this->name != a.name; }
		private:
			std::string name;
			int age;
	};

	// ===== Global operators =====

	std::ostream& operator<<(std::ostream& os, const Name_pairs& pairs){
		for (size_t i = 0; i < pairs.vector().size(); ++i){ 
			std::cout << pairs.vector()[i].Name() << " " << pairs.vector()[i].Age() << '\n';
		}
		return os;
	}
}

int main(){
	name_lib::Name_pairs pairs;

	pairs.read_names();
	pairs.read_ages();
	
	name_lib::Name_pairs a;
	a.read_names();
	a.read_ages();

	std::cout << int(pairs != a);
	
	pairs.sort();
	std::cout << pairs;
}
