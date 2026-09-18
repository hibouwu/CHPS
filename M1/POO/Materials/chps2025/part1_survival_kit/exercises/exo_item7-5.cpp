#include <iostream>
#include "exo_item7-5.h"
#include "exo_item7-5_tools.h"

int main(){
  MyClass c;
  c.print();
  c.addParameter();
  c.print();
  std::cout << "parameter value : " << parameter << std::endl;
  return 0;
}
