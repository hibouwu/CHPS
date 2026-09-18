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
  A(A&& a) : m_i(std::move(a.m_i)) {
    std::cout << "A(A&&)" << std::endl;
  }
  A& operator=(A&& a) {
    m_i = std::move(a.m_i);
    std::cout << "A& operator= (A&& a)" << std::endl;
    return *this;
  }
   
}; 

int main(){
  A a(1); // A(int)
  A a2(a); // A (A const& a)
  A a3; // A()
  a3 = a3; // A& operator= (A const& a)
  A a4(std::move(a)); // A(A&&)
  A a5; // A()
  a5 = std::move(a2); // A& operator= (A&& a)
} //~A()