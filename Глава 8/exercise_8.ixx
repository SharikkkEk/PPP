export module patron;

import std;

constexpr unsigned int UINT_MAX = 4294967295;

export namespace patron_lib{
	struct Name{
		std::string name;
	};

	struct Card_number{
		int n;
	};

	struct Fee{
		Fee(long long x)
			: fee (x) 
		{ 
			if (x < 0 || x > UINT_MAX) 
				throw std::runtime_error("Invalid fee");
		}

		unsigned int fee;
	};

	class Patron{
	public:
		Patron(Name n, Card_number c) : name {n}, number {c} {}
		Patron(Name n, Card_number c, Fee f) : name {n}, number {c}, fee {f} {};

		const std::string& get_name() const { return name.name; }
		int get_number() const { return number.n; }
		int get_fee() const { return fee.fee; }

		void set_fee(long long x);

		bool operator==(Patron& other) const { return this->get_number() == other.get_number(); }
	private:
		Name name;
		Card_number number;
		Fee fee {0};
	};

	void Patron::set_fee(long long x){
		if (x < 0 || x > UINT_MAX) throw std::runtime_error("Invalid fee");
		fee.fee = x;
	}

	bool is_owed(const Patron& p){
		if (p.get_fee() > 0) return true;
		return false;
	}
}
