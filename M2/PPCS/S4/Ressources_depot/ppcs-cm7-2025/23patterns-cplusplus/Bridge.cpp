#include <stdio.h>

/*
 * C++ Design Patterns: BRIDGE
 * http://www.plantuml.com/plantuml/uml/bP7DIiD04CVl-nG37jegDUYnXD36YlJYGRtBTZDAO3-MsTb2KHyepv4NSxEO4b14zvBX_n5-mwm3I-9ej2XcK3_ijdUtC2j4UahB462p3qnISUiil0b8xmoSHvA3CbzaPGcU7ADYR9vRupKQj9m3C3zbTyOln8SGhMMa5waGTcFKqVTV9tEUyYF6ZREAa77IsNoLBlvJgdyfJLSzNowdV6BAMhudyoUWFwLg8QnZ11dW_YgpbFkgL4uxMf4xIbthY5LDRVEAPP7rgYpsrHXzEdfS3G8yCaN5aQJEthRlb8jU8-YPdApI88Jq6GxJTwVBv0eoQ0nm3HxZ8JdGTmSNaQ2rJTzvj8qqG-DIf146RB5EKpJw4m00
 *
 */



#include <iostream>
#include <string>

class Implementor {
public:
  Implementor() { std::cout << "Constructor Implementor" << std::endl; }
  virtual ~Implementor() {}
  virtual std::string operationImp()  const = 0;
 
};

class ConcreteImplementorA : public Implementor {
public:
  ConcreteImplementorA() { std::cout << "Constructor ConcreteImplementorA" << std::endl; }
  ~ConcreteImplementorA() {}
  std::string operationImp() const override { return "operationImp from ConcreteImplementorA\n"; }
};

class ConcreteImplementorB : public Implementor {
public:
  ConcreteImplementorB() { std::cout << "Constructor ConcreteImplementorB" << std::endl; }
  ~ConcreteImplementorB() {}
  std::string operationImp() const override { return "operationImp from ConcreteImplementorB\n"; }
};

class Abstraction {
protected:
  Implementor* protected_implementation;
public:
Abstraction(Implementor* implementation) : protected_implementation(implementation) {
    }
virtual ~Abstraction() {}
virtual std::string operation() const {
    return "Abstraction: Base operation with: " +
           this->protected_implementation->operationImp();
}
  
};

class RefinedAbstraction : public Abstraction {
public:
virtual ~RefinedAbstraction() {}
RefinedAbstraction(Implementor* implementation) : Abstraction(implementation) {
  }
std::string operation() const {  
return "RefinedAbstraction: Extended operation with: " +
           this->protected_implementation->operationImp();
}

};

int main() {

  Implementor* implementation = new ConcreteImplementorA;
  Abstraction* abstraction = new Abstraction(implementation);
  std::cout << abstraction->operation();
  std::cout << std::endl;
  delete implementation;
  delete abstraction;
  implementation = new ConcreteImplementorB;
  abstraction = new RefinedAbstraction(implementation);
  std::cout << abstraction->operation();
  std::cout << std::endl;
  delete implementation;
  delete abstraction;
}