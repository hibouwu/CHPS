#include <iostream>

class MyClass {
private: // can be omitted here
  int const m_i = 10;
public :
  void print() const {std::cout << m_i;}
};

int main(){
  MyClass my_object{};
  my_object.print();
}
