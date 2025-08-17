#include <iostream>
#include <vector>
#include <algorithm>

int find_index(std::vector<std::string> vector, std::string str){
    for(int i = 0; i < vector.size(); ++i){
        if (vector[i] == str) return i;
    }
    
    throw std::runtime_error("string not found");
}

int main(){
    std::cout << "How much names do you wanna enter?\n";
    int N = 0;
    std::cin >> N;
    
    std::vector<std::string> names(N);
    
    for (int i = 0; i < N; ++i){
        std::string str;
        std::cin >> str;
        
        if (!std::cin) throw std::runtime_error("input error");
        
        names[i] = str;
    }
        
    std::vector<int> ages(N);
        
    for (int i = 0; i < N; ++i){
        int a = 0;
        std::cin >> a;
        
        if (!std::cin) throw std::runtime_error("not positive integer number has been entered");
        ages[i] = a;
    }
    
    std::vector<std::string> copy_vector = names;
    std::sort(names.begin(), names.end());
    
    for (std::string& x : names){
        int index = find_index(copy_vector, x);
        
        std::cout << x << ' ' 
                  << ages[index] << '\n';
    }
}

