#include <iostream>
#include <vector>

template<typename T>
struct identify{
    typedef T type;
};

template<typename T>
void print_until_s(std::vector<T>& vector, typename identify<T>::type target){
    for (T x : vector){
        if (x == target)
            return;
        std::cout << x;
    }
}

void print_until_ss(const std::vector<std::string>& vector, std::string str){
    char cnt = 0;
    for (const std::string& x : vector){
        if (x == str)
            ++cnt;
        if (cnt == 2)
            return;
        std::cout << x;
    }
}

int main(){
    std::vector<std::string> v { "1", "2", "3", "3", "5" };
    
    print_until_ss(v, "3");
}
