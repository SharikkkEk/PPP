#include <iostream>
#include <vector>

template<typename T>
T maxv(std::vector<T>& vector){
    T max = vector[0];
    
    for (auto it = (vector.begin()+1); it < vector.end(); ++it){
        max = *it > max ? *it : max;
    }    
    
    return max;
}

int main(){
    std::vector<const char*> price { "aa", "cc", "bb" };
    
    std::cout << maxv(price);
}