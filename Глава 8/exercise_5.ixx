export module book;

import std;

constexpr unsigned int UINT_MAX = 4294967295;

bool isdigit(char ch){
	return ch >= 48 && ch <= 57;
}

bool isalpha(char ch){
	return (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122);
}

export namespace book_lib{
	enum class Genre{
		fiction, nonfiction, periodical, biography, children
	};
	std::vector<std::string> genres { "fiction", "nonfiction", "periodical", "biography", "children" };
	template <typename T>
	int to_int(T x){
		return static_cast<int>(x);
	}

	struct Title { std::string t; };
	struct Author { std::string a; };

	struct Copyright_date{
	public:
		inline Copyright_date(long long x); 

		unsigned int get() const { return d; }
		inline void set(long long x);	

		void error_handled() { error_state = false; }
		bool check_error() const { return error_state; }
	private:
		bool error_state = false;
		unsigned int d;
	};

	inline Copyright_date::Copyright_date(long long x) : d{static_cast<unsigned int>(x)} 
	{
		if (x < 0 || x > UINT_MAX)
			error_state = true;
	}

	inline void Copyright_date::set(long long x) {
		if (x < 0 || x > UINT_MAX) error_state = true;
		else d = x;
	}

	struct ISBN{
	public:
		ISBN(std::string str) : number {str} { error_state = check(number); }
		
		const std::string& get() const{ return number; }
		inline void set(const std::string& str); 
		
		void error_handled() { error_state = false; }
		bool check_error() const { return error_state; }
	private:
		bool check(std::string) const;
		bool error_state = false;
		std::string number;
	};

	inline void ISBN::set(const std::string& str){ 
		error_state = check(str);
		if (!error_state)
			number = str; 
	}
	
	bool ISBN::check(std::string str) const{
		enum class states {
			first_number, get_numbers, digit_letter, end
		};
		unsigned char counter = 0;
		states state = states::first_number;
	
		for (char x : str) {
			switch(state){
			case states::first_number:
				if (!isdigit(x)){
					return true;
				}
				state = states::get_numbers;
				break;
	
			case states::get_numbers:
				if (isdigit(x)) { 
					continue;
				}
				else if (x == '-' && counter < 2){
					++counter;
					state = states::first_number;
				}
				else if (x == '-' && counter == 2){
					state = states::digit_letter;
				}
				else{
					return true;
				}
				break;
	
			case states::digit_letter:
				if (isalpha(x) || isdigit(x)){
					state = states::end;
				}
				else{
					return true;
				}
				break;
	
			case states::end:
				return true;
	
			default:
				throw std::runtime_error("Undefined state");
			}
		}
	
		if (state != states::end){
			return true;
		}
	
		return false;
	}

	class Book{
	public:
		Book(const ISBN& num, const Title& t, const Author& a, const Copyright_date& cd, Genre g) 
			: isbn {num}, title {t}, author {a}, copy_date {cd}, genre{g} { this->error(std::cerr); }

		inline bool error() const;
		inline bool error(std::ostream& os) const;
		bool is_available() const { return available; }

		inline void check_out();
		inline void check_in();

		std::string get_ISBN() const { return isbn.get(); }
		std::string get_Title() const { return title.t; }
		std::string get_Author() const { return author.a; }
		unsigned int get_Date() const { return copy_date.get(); }
		std::string get_Genre() const { return genres[to_int(genre)]; }

		bool operator== (const Book& other) const { return this->get_ISBN() == other.get_ISBN(); }
		bool operator!= (const Book& other) const { return this->get_ISBN() != other.get_ISBN(); }
	private:
		ISBN isbn;
		Title title;
		Author author;
		Copyright_date copy_date;
		Genre genre;

		bool available = true;
	};

	inline bool Book::error(std::ostream& os) const{
		if (isbn.check_error())
			os << "ISBN error" << std::endl;
		if (copy_date.check_error())
			os << "Copyright date error" << std::endl;
		return isbn.check_error() || copy_date.check_error();
	}

	inline bool Book::error() const{
		return isbn.check_error() || copy_date.check_error();
	}

	inline void Book::check_out(){
		if (available)
			available = false;
		else
			std::cout << "The book has already been checked out." << std::endl;
	}

	inline void Book::check_in(){
		if (available)
			std::cout << "The book has already been checked in." << std::endl;
		else
			available = true;
	}

	std::ostream& operator<<(std::ostream& os, const Book& b){
		return os << "Title " << b.get_Title() << std::endl
			<< "Author " << b.get_Author() << std::endl
			<< "Genre " << b.get_Genre() << std::endl
			<< "ISBN " << b.get_ISBN() << std::endl;
	}
}
