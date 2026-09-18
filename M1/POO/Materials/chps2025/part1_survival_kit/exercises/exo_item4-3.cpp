#include <iostream>

// Declaration
float my_sum(float a, float b, float c = 0);

// Definition
float my_sum(float a, float b, float c) {
  return a + b + c;
}

int main() {
  float res = my_sum(1.2,3.4);
  std::cout << "my_sum(1.2,3.4) = " << res << std::endl;
  return 0;
}