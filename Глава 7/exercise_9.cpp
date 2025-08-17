#include <iostream>
#include <vector>

int get_index(std::vector<int>& vector1, std::vector<int>& vector2){
    if (vector1.size() != vector2.size())
        throw std::runtime_error("vectors are not equal");
    
    int index = 0;
    
    for (int i = 0; i < vector1.size(); ++i)
        index += vector1[i]*vector2[i];
    
    return index;
}

int main(){
    std::vector<int> price { 2, 2, 2 };
    std::vector<int> weight { 2, 2, 3 };
    
    std::cout << get_index(price, weight);
}