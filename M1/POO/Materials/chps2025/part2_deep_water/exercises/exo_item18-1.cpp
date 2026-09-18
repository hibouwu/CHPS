#include <iostream>
#include <exception>

void printPositiveInt(int i ) {
  if (i >=0) std::cout << "Int i = " <<i <<std::endl;
  else throw std::invalid_argument("A positive int is required in printPositiveInt");
}

int main() {
    printPositiveInt(1);
    printPositiveInt(-1);
} 