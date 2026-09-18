#include <iostream>

void function(int& i) {
  i++;
}
int main() {
  int i = 3;
  function(i);
  std::cout<< "i = " << i << std::endl; // i = 4 
}