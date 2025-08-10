module symbol_table;

import std;
using namespace std;

// ===== Function definition =====

double Symbol_table::set_value(string s, double d){
	auto it = var_table.find(s);

	if (it != var_table.end()){
		it->second = d;
		return d;
	}

	throw runtime_error("trying to write undefined variable " + s);
}

double Symbol_table::get_value(string s){
	auto it = var_table.find(s);

	if (it != var_table.end())
		return it->second;

	it = const_table.find(s);
	if (it != const_table.end())
		return it->second;

	throw runtime_error("trying to read undefined name " + s);
}
	
double Symbol_table::define_var(string var, double val){ 
	if (is_declared(var))
		throw runtime_error(var + " declared twice");

	var_table[var] = val;
	return val;
}
	
double Symbol_table::define_const(string s, double val){
	if (is_declared(s))
		throw runtime_error(s + " declared twice");

	const_table[s] = val;
	return val;
}
	
bool Symbol_table::is_declared(string var){
	auto it = var_table.find(var);

	if (it != var_table.end())
		return true;

	it = const_table.find(var);
	if (it != const_table.end())
		return true;

	return false;
}
