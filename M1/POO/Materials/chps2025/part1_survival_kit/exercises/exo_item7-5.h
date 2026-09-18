#include <iostream>
#include "exo_item7-5_tools.h"

class MyClass {
private: // can be omitted here
  int  m_i = 10;
public :
  void print() const {std::cout << "MyClass instance data value:" << m_i << std::endl;}
  void addParameter() {m_i += parameter;}
};
