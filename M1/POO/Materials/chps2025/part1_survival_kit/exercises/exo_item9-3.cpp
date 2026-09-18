#include <iostream>

int main() {

  float        r =  3.14;
  float const* float_ptr = &r; // float_ptr points on r
  float const& float_ref =  r; // float_ref references r

  // *float_ptr *= 2; // ERROR pointed value is const
  //  float_ref *= 2; // ERROR referenced value is const

  float r2 = 3.5;
  float_ptr = &r2; // Ok, the pointer is not const
  
  
  float* const float_ptr_const = &r; // const pointer
//  float_ptr_const = &r2; // ERROR pointer is constant
  *float_ptr_const *= 2; // ok, the pointed value is not const
  
  float const * const const_float_const_ptr = &r; // Const pointer of const float !

  // const_float_const_ptr *= 2; // ERROR pointed float is const
  // const_float_const_ptr = &r2; // ERROR pointer is const
  
  return 0;

}