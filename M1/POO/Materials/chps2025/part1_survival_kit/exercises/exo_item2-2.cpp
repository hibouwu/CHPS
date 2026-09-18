#include <iostream>

int main(){
  int i = 0;
  while (i < 10) {
    std::cout << "i = "<< i++ << std::endl;
  }
  i = 0;
  do {
    std::cout << "i = "<< i++ << std::endl;
  } while (i < 10);
}