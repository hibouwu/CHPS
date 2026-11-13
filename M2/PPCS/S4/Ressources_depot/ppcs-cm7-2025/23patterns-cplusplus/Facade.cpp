#include <stdio.h>

/*
 * C++ Design Patterns: FACADE
 * http://www.plantuml.com/plantuml/uml/RP1DJiCm48NtFiMecwv2HDjL5LajXUxefbnWuaofXLqRZus847TXsPuZ5oC_WAYKMVbzCqzlnYkE66AoHkHJsAutw_i7cEQYBMMG6RQei2Bu4901S2gvvaZszbhEhkNyMYx4fn0UrGi-4qmspdf3xp3q9b0KErUHb5r4MqFg_Yze3Cx6u7m43j57NH6GzR46IxQam4Byd9Lbyb_MA9sDqlaeNGXnSf406NR3vaKf2-MC2ylWQZHt9f4Sd4NUSrdafVmTVQezBJi0-nYIYYcWwNkFoA-9m22euVjqR2wG0KL89trmmMfksrDKgZbpRsc-e286TecpRhlcR5k9RwHQ2m5w7vmwKZ_BsdgZ3xgvq8sWKmNT5MBLlf8rtm00
 *
 */

#include <iostream>

class SubSystem1 {
public:
  void suboperation() {
    std::cout << "Simplified SubSystem1 operation" << std::endl;
  }
};

class SubSystem2 {
public:
  void suboperation() {
    std::cout << "Simplified SubSystem2 operation" << std::endl;
  }
};

class SubSystem3 {
public:
  void suboperation() {
    std::cout << "Simplified SubSystem3 operation" << std::endl;
  }
};

class SubSystem4 {
public:
  void suboperation() {
    std::cout << "Simplified SubSystem4 operation" << std::endl;
  }
};

class Facade {
public:
  Facade() {
    std::cout << "Constructor Facade" << std::endl;
    subsystem1 = new SubSystem1();
    subsystem2 = new SubSystem2();
    subsystem3 = new SubSystem3();
    subsystem4 = new SubSystem4();
  }

  ~Facade() {
    if (subsystem1) {
      delete  subsystem1;
    }
    if (subsystem2) {
      delete subsystem2;
    }
  }

  void operationWrapper() {
    std::cout << "begin operationWrapper Facade" << std::endl;
    subsystem1->suboperation();
    subsystem2->suboperation();
    subsystem3->suboperation();
    subsystem4->suboperation();
    std::cout << "end operationWrapper Facade" << std::endl;
  }

private:
  SubSystem1 *subsystem1;
  SubSystem2 *subsystem2;
  SubSystem3 *subsystem3;
  SubSystem4 *subsystem4;
};

int main() {
  Facade facade;
  facade.operationWrapper();
}