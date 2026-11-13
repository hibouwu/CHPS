/*
 * C++ Design Patterns: FACTORY METHOD
 * http://www.plantuml.com/plantuml/uml/RL3DJZen4B_tAIRv7_WRXOrNijcW8F4WOWmNZztkA3LjXqpRmqPz89w35xEK1SF77Fenlu_v6FaWEKHhHD63wTruCNzzWzd3ud4-WLuXKYWZlOSnemp4y2KWnJzubofzsnc69JN_hyJFWKXECGOy5bnV4cWNa5CUuOMfYIeSt3tPnDFkemCk5UWW8PQwGK2x2YrOj3Mo5s9lM7xt-sUAhhLZi4kA4pAKWpEAS1GGf8VdsznlMLUb8aCyP6gbkJSHg-bkNDZDMnOPhygYhlQIHRl2uJQnswqc9qt69fkrOXqWEeI_5QqeCYZUh94J0bH_OhZ9V2kr1vCEZ-a2Jz7tyweGccIb6-H19ZxrjFD1EgLpEK0VG2r9Uvti9P-81m9T0zjHnIYzeZM_
 *
 * 2021 / JMB
 *
 */

#include <iostream>
#include <string>

class Product {
public:
  Product() { std::cout << "Product instancied" << std::endl; }
  virtual ~Product() {}

  virtual void somethingProduct() = 0;
};

class ConcreateProductA : public Product {
public:
  ConcreateProductA() { std::cout << "ConcreateProductA instancied" << std::endl; }
  ~ConcreateProductA() {}

  void somethingProduct() { std::cout << "ProductA has been created" << std::endl; }
};

class ConcreateProductB : public Product {
public:
  ConcreateProductB() { std::cout << "ConcreateProductB instancied" << std::endl; }
  ~ConcreateProductB() {}

  void somethingProduct() { std::cout << "ProductB has been created" << std::endl; }
};

class Creator {
public:
  Creator() { std::cout << "Creator instancied" << std::endl; }
  virtual ~Creator() {}

  virtual Product* factoryMethod() = 0;
};

class ConcreateCreator : public Creator {
public:

  enum TProduct { A, B};
  TProduct private_a;
  ConcreateCreator(  TProduct b) { std::cout << "ConcreateCreator instancied" << std::endl; private_a=b; }
  ~ConcreateCreator() {}

  Product* factoryMethod() { 
      if (private_a==A) {
      return new ConcreateProductA; }
      else if (private_a==B) {
      return new ConcreateProductB; }
      else return 0;
    }
};

int main(int argc, char* argv[]) {
  Creator *creator = new ConcreateCreator(ConcreateCreator::A);

  Product *productA = creator->factoryMethod();
  productA->somethingProduct();

  Product *productB = creator->factoryMethod();
  productB->somethingProduct();

}