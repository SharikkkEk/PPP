export module date;

import std;

export namespace date_lib{
	// ===== Structures =====
	
	enum class Month{
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};
	
	struct Year{
		int value;
	};

	// ===== Class declaration =====

	class Date{
	public:
		Date();
		Date(Year value, Month mm, int dd);
		Date(const Date&);

		int get_year() const;
		int get_month() const;
		int get_day() const;

		void add_day(int n);

		class invalid {};
		long int all_days = 0; // Количество дней с 1 января 1970. Убрать в private
	private:

		Year current_year; // Поменяй на int. В конструкторе инициализируй с помощью y.value
		Month current_month;
		int current_day;

		void update();

		bool is_valid(Year, Month, int day) const;
	};

	bool leapyear(int);
	int last_day(Month, int);

	// ===== Function definition =====

	Date::Date() 
		: current_year{Year{1970}}, current_month{Month::jan}, current_day{1} {};

	Date::Date(Year year, Month month, int days)
		: current_year{year}, current_month{month}, current_day{days}
	{
		if (!(is_valid(year, month, days)))
			throw invalid {};
	
		while (--year.value > 1970){
			bool leap = leapyear(year.value);
			days += 365+leap;
		}
		
		for(int i = 1; i < int(month); ++i){
			all_days += last_day(Month{i}, current_year.value);
		}

		all_days += days;
	}

	Date::Date(const Date& date) 
		: current_year { Year{date.get_year()} },
		  current_month { Month{date.get_month()} },
		  current_day { date.get_day() } {}

	int Date::get_year() const{
		return current_year.value;
	}

	int Date::get_month() const{
		return int(current_month);
	}

	int Date::get_day() const{
		return current_day;
	}

	void Date::add_day(int n){
		all_days += n;
		
		for (int i = 1; i < (int)current_month; ++i){
			n += last_day(Month{ i }, current_year.value);
		}
		n += current_day;

		current_month = Month::jan;
		
		while (n > (365 + leapyear(current_year.value))){
			n -= 365 + leapyear(current_year.value);
			++current_year.value;
		}

		while (n > last_day(current_month, current_year.value)){
			n -= last_day(current_month, current_year.value);
			current_month = Month{ (int)current_month + 1 }; 
		}

		current_day = n;
	}

	bool Date::is_valid(Year y, Month m, int d) const{
		if (y.value < 0 && y.value > 1969)
			return false;

		if (!(0 < int(m) && int(m) < 13))
			return false;

		return 0 < d && d <= last_day(m, y.value);
	}

	// ===== Auxiliary =====

	bool leapyear(int n){ 
		return (n % 400 == 0) || (n % 4 == 0 && n % 100 != 0);
	}
	
	int last_day(Month m, int y){
		switch(m){
		case Month::jan:
			return 31;
		case Month::feb:
			if (leapyear(y))
				return 29;
			return 28;
		case Month::mar:
			return 31;
		case Month::apr:
			return 30;
		case Month::may:
			return 31;
		case Month::jun:
			return 30;
		case Month::jul:
			return 31;
		case Month::aug:
			return 31;
		case Month::sep:
			return 30;
		case Month::oct:
			return 31;
		case Month::nov:
			return 30;
		case Month::dec:
			return 31;
		default:
			throw std::runtime_error("Invalid month");
		}
	}
	
	/*int week_of_year(const Date& d){
		int day = d.get_day();
		return (day + 6) / 7;
	}*/

	/*Date next_workday(const Date& current){ // Первый день недели воскресенье
		int x = current.get_day()/7;
		int y = (x + 6) / 7;

		Date date = current;
		date.add_day((x == y) ? 1 : 2); 
		// Единственный случай, при котором рабочий день будет послезавтра - суббота

		return date;
	}*/

	std::ostream& operator<<(std::ostream& os, const Date& date){
		return os << date.get_year() << '/'
			  << date.get_month() << '/'
			  << date.get_day();
	}
}
