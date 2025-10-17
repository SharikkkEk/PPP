#include "exercise_13.h"
#include <stdexcept>

namespace ratio_lib{
	Rational::Rational(int n, int d):
		num {n}, denum {d}
	{	if (d == 0)
			throw std::runtime_error("Denum can't be 0");
	}

	Rational::Rational(): num{0}, denum{1} {}

	void Rational::set_denum(int n){
		if (n == 0)
			throw std::runtime_error("Denum cannot equal 0");
		denum = n;
	}

	void Rational::operator=(Rational another){
		this->num = another.num;
		this->denum = another.get_denum();
	}

	bool operator==(Rational n1, Rational n2) {
		return n1.num == n2.num && n1.get_denum() == n2.get_denum();
	}
	
	Rational operator+(Rational n1, Rational n2) {
		Rational temp;
		temp.num = n1.num * n2.get_denum() + n2.num * n1.get_denum();
		temp.set_denum(n1.num * n2.get_denum());
		return temp;
	}

	Rational operator*(Rational n1, Rational n2) {
		Rational temp;
		temp.num = n1.num * n2.num;
		temp.set_denum(n1.get_denum() * n2.get_denum());
		return temp;
	}

	Rational operator-(Rational n1, Rational n2) {
		Rational temp;
		temp.num = n1.num * n2.get_denum() - n2.num - n1.get_denum();
		temp.set_denum(n1.num * n2.get_denum());
		return temp;
	}

	Rational operator/(Rational n1, Rational n2) {
		Rational temp;
		temp.num = n1.num * n2.get_denum();
		temp.set_denum(n1.get_denum() * n2.num);
		return temp;
	}
};
