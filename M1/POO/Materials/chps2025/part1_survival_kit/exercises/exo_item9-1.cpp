#include <iostream>

int main() {
  
  float* float_ptr = new float{3.14}; // new returns an float address

  *(float_ptr) *= 2; // use * operator to get the float value

  std::cout << "float_ptr = " << float_ptr << std::endl; // pointer address (hexadecimal)
  std::cout << "float value = "<< *float_ptr << std::endl; // pointed variable value

  delete float_ptr; // use delete to release memory
  return 0;
}