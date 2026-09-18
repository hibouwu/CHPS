#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

void func(std::vector<int> && v){
    std::copy(v.begin(),v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main(){
    func(std::vector<int>{1,2,3});
    std::vector<int> v{4,5,6};
    // func(v); // Compile-time error, no match
    func(std::move(v));
}