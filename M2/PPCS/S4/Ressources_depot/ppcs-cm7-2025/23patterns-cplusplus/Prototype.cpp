#include <stdio.h>

/*
 * C++ Design Patterns: PROTOTYPE
 * http://www.plantuml.com/plantuml/uml/XP71JW8n48RlVOf9F2nerWqSoMP395w5A1TFf5i6hUcspNHAGjHtySfpy6BM1fQ39CnfC__t_pEpdGQMnB4peYfWyJnVpfUlYqSeAf5AMqRQI8Mm8CUETnxXKq2g6r36MHmCnRSGoiWGO6OqMZxgTn2GUzFWRB_rmmoKu4bl9UFAdxIZKUMSrVzyPnKXOvyrwcTTPyUNs7UzHi3Eymuwx5ga8CJnYh9ipZUBy_hrLrbUsEGgCHR2EaQG0Pv6UPEwRMhbZAC9kPqq3oPYq-DrbQMchjhcH2zJV_BNW1cXPEsiD5bxyOUzqXkDO0hNVY23bmJHWd8sC4N560ciwxh37ef-Hf7DYTQ9abOb_ne3v8G0XnzWabiaC9Z_cNnBUeJ-jUu5sZLOnoYcwIjsvXS0
 *
 */

#include <iostream>
#include <string>

class Prototype {
public:
  Prototype() { std::cout << "Constructor Prototype" << std::endl; }
  virtual ~Prototype() {std::cout << "Destructor Prototype" << std::endl;}
  virtual Prototype* clone() = 0;
  virtual void checkPrototype() = 0;
};

class ConcretePrototype1 : public Prototype {
public:
  ConcretePrototype1() { std::cout << "Constructor ConcretePrototype1" << std::endl; }
  ~ConcretePrototype1() {std::cout << "Destructor ConcretePrototype1" << std::endl;}
  Prototype* clone() { std::cout << "Clone ConcretePrototype1" << std::endl; return new ConcretePrototype1; }
  void checkPrototype() { std::cout << "Prototype1 has been created" << std::endl; }
};

class ConcretePrototype2 : public Prototype {
public:
  ConcretePrototype2() { std::cout << "Constructor ConcretePrototype2" << std::endl; }
  ~ConcretePrototype2() {std::cout << "Destructor ConcretePrototype2" << std::endl;}
  Prototype* clone() { std::cout << "Clone ConcretePrototype2" << std::endl; return new ConcretePrototype2; }
  void checkPrototype() { std::cout << "Prototype2 has been created" << std::endl; }
};

class Client {
public:
  Client() { private_prototype = nullptr; std::cout << "Constructor Client" << std::endl; }
  ~Client() {
    if (private_prototype) {
      delete private_prototype;
    }
  }

  void setPrototype(Prototype *p) {
    std::cout << "Client setPrototype" << std::endl;
    if (private_prototype) {
      delete private_prototype;
    } 
    private_prototype = p;
  }

  Prototype* client_clone() {
    if (!private_prototype) {
      return nullptr;
    }
    std::cout << "Clone() Client" << std::endl;
    return private_prototype->clone(); 
  }

private:
  Prototype *private_prototype;
};

int main(int argc, char* argv[]) {
  Client client;
  client.setPrototype(new ConcretePrototype1);
  Prototype *p1 = client.client_clone();
  p1->checkPrototype();
  client.setPrototype(new ConcretePrototype2);
  Prototype *p2 = client.client_clone();
  p2->checkPrototype();
}