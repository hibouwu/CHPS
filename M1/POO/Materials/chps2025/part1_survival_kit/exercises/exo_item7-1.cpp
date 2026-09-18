#include <iostream>

class MyClass {
public :
  int i =0;
  void print() {std::cout << i;}
};

int main(){
  MyClass my_object{};
  my_object.i; // error i is private
  my_object.print();// error print is private
}
