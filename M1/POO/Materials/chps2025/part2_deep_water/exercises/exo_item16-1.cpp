#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main() {
    std::vector<int> vec {1,2,3};
    std::cout << "vec address " << vec.data() << std::endl; 
    std::vector<int> vec2 = std::move(vec);
    std::cout << "vec2 : ";
    std::copy(vec2.begin(),vec2.end(),std::ostream_iterator<int>(std::cout," "));
    std::cout << std::endl;
    std::cout << "vec size " << vec.size() << std::endl; 
    std::cout << "vec address " << vec.data() << std::endl;
    std::cout << "vec2 address " << vec2.data() << std::endl;
}