import std;
import book;
import patron;
import date;

using namespace book_lib;
using namespace patron_lib;
using namespace date_lib;

namespace libraries_lib{
	struct Transaction{
		Book& checked_out_book;
		Patron& Borrower;
		Date date;
	};

	class Library{
	public:
		void add_book(Book);
		void add_patron(Patron);

		bool check_out(Book b, Patron p, Date date);
		
		std::vector<Patron> owed_patrons();
	private:
		std::vector<Book> books;
		std::vector<Patron> patrons;
		std::vector<Transaction> transactions;
	};

	bool Library::check_out(Book b, Patron p, Date date){
		auto lib_b = std::find(books.begin(), books.end(), b);
		if (lib_b == books.end()){
			std::cerr << "The book is not in library" << std::endl;
			return false;
		}

		auto lib_p = std::find(patrons.begin(), patrons.end(), p);
		if (lib_p == patrons.end()){
			std::cerr << "The patron is not in library" << std::endl;
			return false;
		}

		if (!(lib_b->is_available())){
			std::cerr << "The book is not available" << std::endl;
			return false;
		}

		if (is_owed(*lib_p)){
			std::cerr << "The patron owed" << std::endl;
			return false;
		}

		transactions.push_back( Transaction{*lib_b, *lib_p, date} );
		lib_b->check_out();
		return true;
	}

	std::vector<Patron> Library::owed_patrons(){
		std::vector<Patron> owed;
		int n = 0;

		for ( const Patron& x : patrons ){
			if (is_owed(x)) ++n;
		}
		owed.reserve(n);

		for (int i = 0; i < patrons.size(); ++i){
			if (i == n) owed.push_back(patrons[i]);
		}

		return owed;
	}

	void Library::add_book(Book b){
		books.push_back(b);
	}

	void Library::add_patron(Patron p){
		patrons.push_back(p);
	}
}

using namespace libraries_lib;

int main(){
	Book X{ ISBN {"1-2-3-4"}, Title {"213"}, Author {"2313"}, Copyright_date{1234}, Genre::fiction };
	Patron P { Name {"J"}, Card_number {1234} };
	Date today { Year{2000}, Month::jan, 1 };
	Library lib;

	for (int i = 0; i < 10; ++i){
		for (int x = 0; x < 2; ++x){
			lib.add_patron( Patron { Name {"A"}, Card_number {i}, Fee {x}} );
		}
	}

	lib.add_book(X);
	lib.add_patron(P);

	lib.check_out(X, P, today);

	auto v = lib.owed_patrons();

	for (auto i : v)
		std::cout << i.get_number();
}
