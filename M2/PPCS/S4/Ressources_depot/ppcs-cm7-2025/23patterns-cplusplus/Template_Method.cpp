#include <stdio.h>

/*
 * C++ Design Patterns: TEMPLATE METHOD
 * http://www.plantuml.com/plantuml/uml/PL5BJiCm4Dtx52EnAAXjedPPHL4_hSI2KXQvWECCn99Z1tjIgGBkGy-HYp59gGJDhCRFxwEdMGQIdfhAY7W4sMx_yhJATh3VPO-7BOnYmQEC305MUI0l5MtwLq9OrKOIxf5ALzm_W9B6mA56BqaxEvlC9r4KfV0XW6SCj_mUlliZ649pXhwkyHjdbKV2I_pLTI0V3-IbBX0ud4vGOPMZ3qBSTFcSJl_x2s4T8SW0ppC1F4cU9iePvnVUdQHPcmRJxBSHN2ebSKz8apXFhvhiLEEY0s2DfJngvwNf_xRj-LLRJT1OaERDUKrbXH3U6pH8x5auIptJO82gFNS9l1sr9wPqO606QCldiqgtPqPgwS58w6Mggu6WkbRjDs4aq1RGjH9BtlZUFm00
 *
 */


#include <iostream>

class AbstractClass {
public:
  virtual ~AbstractClass() {}

  void templateMethod() {
    std::cout << "generic design step1" << std::endl;
    Operation1();
    std::cout << "generic design step2" << std::endl;
    Operation2();
  }

  virtual void Operation1() = 0;
  virtual void Operation2() = 0;
};

class ConcreteClass : public AbstractClass {
public:
  ~ConcreteClass() {}

  void Operation1() {
    std::cout << "ConcreteClass Operation 1" << std::endl;
  }

  void Operation2() {
    std::cout << "ConcreteClass Operation 2" << std::endl;
  }
};

int main() {
  AbstractClass *templateClass = new ConcreteClass();
  templateClass->templateMethod();
}