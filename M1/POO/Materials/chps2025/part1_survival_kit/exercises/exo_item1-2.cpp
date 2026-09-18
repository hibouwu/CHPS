#include <iostream>
#include <memory>

class Parent {
public:
  void print() {
    std::cout << "Parent" << std::endl;
  }
};

class Child : public Parent {
public:
  void display() {
    std::cout << "Child" << std::endl;
  }
};

int main() {

  std::unique_ptr<Parent> p = std::make_unique<Child>();
  p->print(); // OK: Parent class method
  return 0;
}
