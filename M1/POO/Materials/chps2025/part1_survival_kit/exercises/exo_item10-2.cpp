#include <iostream>

struct A{
    void print() const {std::cout << "print A\n";}
    void modify() {std::cout << "modify A\n";}
};

void apply_ref(A& a){
    std::cout << "apply_ref(A&)" << std::endl;
    a.modify();
}

void apply_const_ref(A const& a){
    std::cout <<"apply_const_ref(A const&)" << std::endl;
    a.print();
}

int main() {
    A a{};
    apply_ref(a);
    apply_const_ref(a);
}