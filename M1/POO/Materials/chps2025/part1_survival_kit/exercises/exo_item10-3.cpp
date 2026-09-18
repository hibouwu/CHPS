#include <iostream>

class A {
  int* m_i = nullptr;
public:
  A(int val) : m_i(new int(val)) {}
  ~A() {delete m_i;}
  A(A const&) = delete;
  A& operator=(A const&) = delete;

  void print() const {
    std::cout << "*(A.m_i) = " << *m_i << std::endl;
  }

  void set(int i) {
    *m_i = i;
  }

};

void print_object(A const& a){a.print();}

void modify_object(A & a, int i) {a.set(i);}

int main() {
  A a (1);
  print_object(a);
  modify_object(a,2);
  print_object(a);
  return 0;
}