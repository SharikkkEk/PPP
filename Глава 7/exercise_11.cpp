#include <iostream>
#include <vector>
#include <algorithm>

struct specs{
    int max;
    int min;
    double mean;
    double median;

    specs(int x) : max{x}, min{x}, mean{x}, median{0} {};
};

specs get_specs(std::vector<int> vector){
    if (vector.size() == 0)
        return specs(vector[0]);
    
    specs current(vector[0]);

    for (int elem : vector){
        if (current.max < elem)
            current.max = elem;
        else if (current.min > elem)
            current.min = elem;
            
        current.mean += elem;
    }
    current.mean /= vector.size();
    
    std::sort(vector.begin(), vector.end());
    if (vector.size() % 2 == 0)
        current.median = (vector[vector.size()/2-1] + vector[vector.size()/2])/2;
    else
        current.median = vector[vector.size()/2];
        
    return current;
}

int main() {
    std::vector<int> str {1, 2, 3, 4};
    std::vector<int> str1 {1, 2, 3, 4, 5};
    
    specs a = get_specs(str);
    specs b = get_specs(str1);
    
    std::cout << a.min << ' ' << a.max << ' '
              << a.mean << ' ' << a.median << '\n';
    std::cout << b.min << ' ' << b.max << ' '
              << b.mean << ' ' << b.median << '\n';
}
