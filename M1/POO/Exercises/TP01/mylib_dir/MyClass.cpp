#include "MyClass.h"
#include <iostream>

namespace MyLib {
    MyClass::MyClass() {
        std::cout << "MyClass constructor called" << std::endl;
    }

    void MyClass::print( std::string message ) {
        std::cout << message << std::endl;
    }

    int MyClass::value() const {
        return 42;
    }
}
