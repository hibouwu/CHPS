#include <iostream>

template<typename... T>
void print(T&&... t) {
    (std::cout << ... << t )  << std::endl; 
}

int main() {
  print(1);
  print(1,'c')
  print(1,"Hello World",3.f);
}
