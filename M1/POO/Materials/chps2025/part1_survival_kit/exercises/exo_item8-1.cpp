#include <iostream> 

struct Parent{
    int v;
    void print_parent(){
        std::cout << "Parent ; v = " << v << std::endl;
    }
};

struct Son : public Parent {
    void print() {
        std::cout << "The Child, ";
        print_parent();
    }
    void set_value(int val){
        v = val;
    }
};

struct Son2 : protected Parent {
};

struct Son3 : private Parent {
};

struct GrandSon : Son {
    void print() {
        std::cout << "The Grand Child, ";
        print_parent(); // ok if public or protected, KO if private
    }
    void print() {
        std::cout << "The Grand Child, ";
        Son::print(); // always ok
    }
};


int main(){
  Parent p{42};
  p.print_parent(); // output : "Parent ; v = 42"
  std::cout << "parent value " << p.v << std::endl; // output : "parent value 42"
  Son s{};
  s.set_value(42);
  s.print(); // output "The Child, Parent ; v =42"
  s.print_parent(); // output : "Parent ; v = 42"
  std::cout << s.v; // output : "42"
}