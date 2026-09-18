#include <numeric>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>

struct Functor {
    int operator() (int sum, int current_value) {
        return (sum+2*current_value);
    }
};

int main() {
    std::vector<int>  v (100,0);
    std::iota(v.begin(),v.end(),1);
    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," " ));
    std::cout << " sum : " << std::accumulate(v.begin(),v.end(),0);
    std::cout << " sum : " << std::accumulate(v.begin(),v.end(),0,Functor{});
    return 0;
    
}