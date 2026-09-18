#include <iostream>

int main() {

  float        r =  3.14;
  float* float_ptr = &r; // float_ptr pofloats on r
  float& float_ref =  r; // float_ref references r

  *float_ptr *= 2; 
  float_ref *= 2; 

  std::cout << "       r = " << r << std::endl; 
  std::cout << " float_ptr = " << float_ptr << std::endl; // pointer address (hexadecimal)
  std::cout << "*float_ptr = "<< *float_ptr << std::endl; //    pointed variable value
  std::cout << " float_ref = " << float_ref << std::endl; // referenced variable value 

  return 0;

}