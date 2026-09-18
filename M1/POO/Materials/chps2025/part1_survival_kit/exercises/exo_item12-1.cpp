#include <iostream>

template <typename T>
void f(T& a) { ++a; std::cout << "a= "<< a << std::endl; }

int main(){
    int i = 0;
    f(i);
    float pi = 3.14;
    f(pi);
 }
