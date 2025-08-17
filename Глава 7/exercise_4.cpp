import std;
import print_vector;
import fibonacci;

int main(){
	std::string str;
	std::vector<int> v;

	fibonacci(102'191'999, 40'299, v, 11);
	print_vector(v, str);

	std::cout << str;
}
