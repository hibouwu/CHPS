#include <iostream>
#include <memory>

int main() {
  std::shared_ptr<double> d_ptr = std::make_shared<double>(3.14);
  std::shared_ptr<double> d_ptr2 = d_ptr;
  (* d_ptr)*=2;
  std::cout << *d_ptr2 << std::endl; 
  return 0;
}