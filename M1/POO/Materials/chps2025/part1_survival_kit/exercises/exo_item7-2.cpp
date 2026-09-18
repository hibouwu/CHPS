#include <iostream>

class MyClass {
private: // can be omitted here
  int i =0;
public :
  void print() {std::cout << i;}
};

int main(){
  MyClass my_object{};
  my_object.print();
}
