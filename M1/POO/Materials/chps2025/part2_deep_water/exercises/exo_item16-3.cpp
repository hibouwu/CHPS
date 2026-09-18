#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

void func(std::vector<int> && v){
    std::cout << "v address after call " << v.data() << std::endl;
    std::vector<int> v_copy {v};
    std::cout << "v copy address " << v_copy.data() << std::endl;
    std::vector<int> v_move {std::move(v)};
    std::cout << "v move address " << v_move.data() << std::endl;
    std::copy(v.begin(),v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main(){
    func(std::vector<int>{1,2,3});
    std::vector<int> v{4,5,6};
    std::cout << "v address before call " << v.data() << std::endl;
    // func(v); // Compile-time error, no match
    func(std::move(v));
}