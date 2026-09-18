#include <iostream>

template<typename... T>
T sum(T&&... t) {
    auto res = (... + t);
    std::cout << res << std::endl;
    return res;
}


int main(){
  auto result = 0;
  result = sum(1,2);
  result = sum(1,2,3);
  result = sum(1,2,4,5,6);
  return 0;
}