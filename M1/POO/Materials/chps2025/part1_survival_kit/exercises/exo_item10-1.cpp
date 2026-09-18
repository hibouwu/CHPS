#include <iostream>
struct A{
  int m_i = 0;
  A() {std::cout << "A()" << std::endl;};
  A(int const i) : m_i (i) {
    std::cout << "A(int)" << std::endl;}
  ~A() {std::cout << "~A()" << std::endl;}
  A(A const& a) {
    m_i = a.m_i;
    std::cout << "A(A const& a)" << std::endl;
  } 
  A& operator= (A const& a) {
    m_i = a.m_i;
    std::cout << "A& operator= (A const& a)" << std::endl;
    return *this;
  }
   
}; 

int main(){
  A a(1); // A(int)
  A a2(a); // A (A const& a)
  A a3; // A()
  a3 = a2; // A& operator= (A const& a)
  std::cout << "a3.m_i = " << a.m_i << "\n";
} //~A()