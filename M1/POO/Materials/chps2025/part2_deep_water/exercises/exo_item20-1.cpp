#include <iostream>

struct A{
  A() = default;
  A(A const&) {std::cout << "A(A const&)" << std::endl;}
  A(A&&) {std::cout << "A(A&&)" << std::endl;}
};

struct B {
  A m_a;
  template <typename T> 
  B(T&& t) : m_a{std::forward<T>(t)} {}
};

int main() {
  A a{};
  B b(A{}); // A(A&&)
  B b2(a); // A(A const&)
  return 0;
}