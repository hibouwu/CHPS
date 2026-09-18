#include <iostream>

// Declaration
float my_sum(float a, float b, float c);

// Definition
float my_sum(float a, float b, float c) {
  return a + b + c;
}

int main() {
  float res = my_sum(1.2,3.4,4.5);
  std::cout << "my_sum(1.2,3.4,4.5) = " << res << std::endl;
  return 0;
}