namespace ratio_lib{
	class Rational{
	public:
		Rational(int n, int d);
		Rational();
		operator double() const { return static_cast<double>(this->num)/this->get_denum(); }

		void operator=(Rational another);

		int num;
		int get_denum() const { return denum; }
		void set_denum(int n);
	private:
		int denum;
	};

	bool operator==(Rational n1, Rational n2);
	Rational operator+(Rational n1, Rational n2);
	Rational operator-(Rational n1, Rational n2);
	Rational operator/(Rational n1, Rational n2);
	Rational operator*(Rational n1, Rational n2);
}
