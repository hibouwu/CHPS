#include <stdio.h>

/*
 * C++ Design Patterns: SINGLETON
 * http://www.plantuml.com/plantuml/uml/LP11ImCn48Nl-HNljeheuhKiIx6856Gzj7V9PeSI66VQJI8KyV_uF_nZpWOhEAVaVUybZrcdxETStjYr3NRRuUdvSVyoe6cTJM2V4dPH3anP1HyEDhUmJ8u1HUAfq6iKkqkW2cykSFkhNbsxJ-T4Cy4d3FVLrOrz5vHrNirwzlp0XVg_Rxgsehvhn_xYtf-Fj5e4R6QozrKyLxPPAX9E9K88HoeP_btZR4fJJ4bKcF2l8kLgdrICboMbKJAcneVm_PLmO1qztpcI2KjljxQJRUW7
 *
 */



#include <iostream>
#include <string>

class Singleton {
public:
//remove some standard method
//copy constructor and affectation
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

  static Singleton* Instance() {
    if (!unique_instance) {
      unique_instance = new Singleton();
    } else {std::cout << "constructor : Unique Singleton already created" << std::endl;}
    return unique_instance;
  }

  void checkSingleton() { std::cout << "checkSingleton" << std::endl;
  if (!unique_instance) { std::cout << "checkSingleton : Unique Singleton not created" << std::endl; 
  } else  { 
      std::cout << "checkSingleton : Unique Singleton already created" << std::endl;
   }
  }
private:
  Singleton() { std::cout << "Unique Singleton Constructor" << std::endl; }
  static Singleton* unique_instance;
};

//global variable
Singleton* Singleton::unique_instance = nullptr;

int main(int argc, char* argv[]) {
  Singleton *singleton = Singleton::Instance();
  singleton->checkSingleton();
  //we create a new singleton2 but...
  Singleton *singleton2 = Singleton::Instance();
  singleton2->checkSingleton();
}