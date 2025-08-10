export module symbol_table;

import std;
using namespace std;

export class Symbol_table{
private:
	map<string, double> var_table;
	map<string, double> const_table;
public:
	double set_value(string s, double d);
	double get_value(string s);
	double define_var(string var, double val); // Возможно стоит объединить с define_const
	double define_const(string s, double val);
	bool is_declared(string var);
};

export Symbol_table names;
