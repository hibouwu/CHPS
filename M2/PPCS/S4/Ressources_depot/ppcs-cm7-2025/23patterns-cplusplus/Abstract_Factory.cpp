/*
 * C++ Design Patterns: ABSTRACT FACTORY
 * http://www.plantuml.com/plantuml/uml/VP51ojim48NtEiN0lqXBCARRO4piG9PjIBFfKfQdZOeifQDnmRIzIvVrENonIgeJ-XiJGMBptZVFevczPqdSTqRa6wZgZvTpTRZ0CVnzE7-2JIx2KKPw3mUZqR8GsZBIPwaGgiOpISN7y7Cqm0y1uRo08fIC9t9jhxXwytPDheFywn7jh29aV1sqNG_QhWMjT3Nx8Um5lEkGhzf-cSN_FtwF3-1s7LoGzHFogbi4x6uyG8TTW-I5M8wf-9bbookBPTSHUhJsrAt5lyr0bfNBbQnPSvaGrZ62zF3-NPfhqPI5SiRHZjmWJMrwBEyrCESLUIBA8c_AUz5bkE4k2d28Uz7EIfEy4rA734Q2ecbC3hGRrtn5zl2jrmdopWP4JwE7wJUqw27DEZwTjJtwH25349sQnc1uQJt8xqvJB348Dvf6fJrIOjje6-nfJef1YgO_Z09j2_7MOX_U-ixy1G00
 * 2021 / JMB
 *
 */


#include <iostream>

class AbstractProductA {
public:
  AbstractProductA() { std::cout << "AbstractProductA instancied" << std::endl; }
  virtual ~AbstractProductA() {}
  virtual void somethingProduct() = 0;
};

class AbstractProductB {
public:
  AbstractProductB() { std::cout << "AbstractProductB instancied" << std::endl; }
  virtual  ~AbstractProductB() {}
  virtual void somethingProduct() = 0;
};

class ProductA1 : public AbstractProductA {
public:
  ProductA1() { std::cout << "ProductA1 instancied" << std::endl; }
  ~ProductA1() {}
  void somethingProduct() { std::cout << "ProductA1 has been created" << std::endl;}

};

class ProductA2 : public AbstractProductA {
public:
  ProductA2() { std::cout << "ProductA2 instancied" << std::endl; }
  ~ProductA2() {}
  void somethingProduct() { std::cout << "ProductA2 has been created" << std::endl; }

};

class ProductB1 : public AbstractProductB {
public:
  ProductB1() { std::cout << "ProductB1 instancied" << std::endl; }
  ~ProductB1() {}
  void somethingProduct() { std::cout << "ProductB1 has been created" << std::endl; }

};

class ProductB2 : public AbstractProductB {
public:
  ProductB2() { std::cout << "ProductB2 instancied" << std::endl; }
  ~ProductB2() {}
  void somethingProduct() { std::cout << "ProductB2 has been created" << std::endl; }

};

class AbstractFactory {
public:
  AbstractFactory() { std::cout << "AbstractFactory instancied" << std::endl; }
  virtual ~AbstractFactory() {}
  virtual AbstractProductA* createProductA() = 0;
  virtual AbstractProductB* createProductB() = 0;
};

class ConcreateFactory1 : public AbstractFactory {
public:
  ConcreateFactory1() { std::cout << "ConcreateFactory1 instancied" << std::endl; }
  ~ConcreateFactory1() {}
  AbstractProductA* createProductA() { return new ProductA1; }
  AbstractProductB* createProductB() { return new ProductB1; }
};

class ConcreateFactory2 : public AbstractFactory {
public:
  ConcreateFactory2() { std::cout << "ConcreateFactory2 instancied" << std::endl; }
  ~ConcreateFactory2() {}
  AbstractProductA* createProductA() { return new ProductA2; }
  AbstractProductB* createProductB() { return new ProductB2; }
};

int main(int argc, char* argv[]) {
  AbstractFactory* cf1 = new ConcreateFactory1();
  AbstractProductA* productA1 = cf1->createProductA();
  productA1->somethingProduct();
  AbstractProductB* productB1 = cf1->createProductB();
  productB1->somethingProduct();

  AbstractFactory* cf2 = new ConcreateFactory2();
  AbstractProductA* productA2 = cf2->createProductA();
  productA2->somethingProduct();
  AbstractProductB* productB2 = cf1->createProductB();
  productB2->somethingProduct();

}