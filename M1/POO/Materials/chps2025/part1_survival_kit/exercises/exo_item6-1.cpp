#include <iostream>

int multiple(int a, int b) {
  return a*b;
}

int multiple(int a) {
  return a*10;
}

int main() {
  std::cout << "multiple(2,3) = " << multiple(2,3) << std::endl;
  std::cout << "multiple(2) = "  << multiple(2) << std::endl;
}
