#include <stdio.h>

/*
 * C++ Design Patterns: DECORATOR
 * http://www.plantuml.com/plantuml/uml/ROvDJiCm48NtFiL8BCgFGiIsYg92ovQYqZsQEWDrvTXXF4QgWFlGS_HYE97weuHPZTxxvisR146MM5kLZs3sE9qlxfVp1OnobSOu8Nv3JJ3rTUCTEO4l1Makm3V4ACQxoolrevIs64B2d6OIwkCt_-CpqZwfdW-fvrGhPD2m-KIXLtr873xhfGoVdTeKtrasBDa3JhNEZ2oxFjEFMtimBAAKyqA00Pxkkah5gYoqjvx7xBTe7soayaWNUMULHRug3_Hosz2u5U15E6g9ZBRpdebh4gX6-vsGgvWWEl2hJT82kW3h_OwDu3j1ZIPq9-G0DpuAEabmCjBfsbS4LGivi__bj6yTrkOZqgrAiT3sLvEqnTh-0G00
 *
 */

#include <iostream>
#include <string>

class Component {
public:
  virtual ~Component() {}

  virtual void operation() = 0;
};

class ConcreteComponent : public Component {
public:
  ~ConcreteComponent() {}

  void operation() {
    std::cout << "Base operation for ConcreteComponent" << std::endl;
  }
};

class Decorator : public Component {
public:
  ~Decorator() {}

  Decorator(Component *c) : private_component(c) {}

  virtual void operation() {
    private_component->operation();
  }
private:
  Component *private_component;
};

class ConcreteDecoratorA : public Decorator {
public:
  ConcreteDecoratorA(Component *c) : Decorator(c) {}

  void operation() {
    Decorator::operation();
    std::cout << "Augmented operation for ConcreteDecoratorA" << std::endl;
  }
};

class ConcreteDecoratorB : public Decorator {
public:
  ConcreteDecoratorB(Component *c) : Decorator(c) {}

  void operation() {
      Decorator::operation();
      std::cout << "Augmented operation for ConcreteDecoratorB" << std::endl;
  }
};

int main() {
  Component *cc = new ConcreteComponent();
  ConcreteDecoratorA *cda = new ConcreteDecoratorA(cc);
  ConcreteDecoratorB *cdb = new ConcreteDecoratorB(cc);

  cda->operation();
  cdb->operation();

}