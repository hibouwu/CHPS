#include <iostream>
#include <exception>


struct exception : std::runtime_error{
    exception(int bad_value, std::string const& message) : std::runtime_error{message}, m_bad_value{bad_value} {}
  int m_bad_value;
};

void printPositiveInt(int i ) {
  if (i >=0) std::cout << "Int i = " <<i <<std::endl;
  else throw exception{i,"A positive int is required in printPositiveInt"};
}

int main() {
  try {
    printPositiveInt(1);
    printPositiveInt(-1);
  }
 
  catch (exception& e) {
    std::cout << e.what() << std::endl;
    std::cout << "bad value : " << e.m_bad_value << std::endl;
  }
} 