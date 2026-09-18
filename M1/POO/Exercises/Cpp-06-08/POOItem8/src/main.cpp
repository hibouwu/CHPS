#include "parent.hpp"

int main(){
  Parent p{42};
  p.print_parent(); // output : "Parent ; v = 42"
  std::cout << "parent value " << p.get_v() << std::endl; // output : "parent value 42"
  Son s{};
  s.set_value(42);
  s.print(); // output "The Child, Parent ; v =42"
  s.print_parent(); // output : "Parent ; v = 42"
  std::cout << s.get_v(); // output : "42"

  Point2D pt{3.0, 4.0};
  pt.print();
  std::cout << "Distance to origin: " << pt.distance_to_origin() << std::endl;

  
  return 0;
}

