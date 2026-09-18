#include <iostream>

// With a function call
template <typename T>
void display(T&& arg){
  std::cout << arg << ' ' ;
}

template <typename...T>
void print2(T&&... args) {
  (display(std::forward<T>(args)),...);
  std::cout << std::endl;
}


// Without
template <typename...T>
void print(T&&... args) {
  ((std::cout << args << ' '),...);
  std::cout << std::endl;
}



int main() {
  print(1);
  print(1,'c');
  print(1,"Hello World",3.f);
}