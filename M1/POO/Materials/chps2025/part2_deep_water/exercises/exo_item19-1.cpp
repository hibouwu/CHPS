#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Interface {
public : 
  virtual void compute() = 0;
  virtual ~Interface() = default;
};

class Implem1 : public Interface {
public:
  void compute() override {std::cout << "Implem1::compute()" << std::endl;}
  ~Implem1(){std::cout << "~Implem1"<< std::endl;}
};

class Implem2 : public Interface {
 public:
 void compute() override {std::cout << "Implem2::compute()" << std::endl;}
 ~Implem2(){std::cout << "~Implem2"<< std::endl;
};

void apply(Interface* interface){
  interface->compute();
}

void apply(std::unique_ptr<Interface>& interface){
  interface->compute();
}

int main() {
  Interface* interface1 = new Implem1{};
  Interface* interface2 = new Implem2{};
  apply(interface1);
  apply(interface2);
  delete interface1;
  delete interface2;

  std::unique_ptr<Interface> smart_interface1 = std::make_unique<Implem1>();
  std::unique_ptr<Interface> smart_interface2 = std::make_unique<Implem2>();
  apply(smart_interface1);
  apply(smart_interface2);
  // or 
  smart_interface1 = std::make_unique<Implem2>();
  apply(smart_interface1);
}