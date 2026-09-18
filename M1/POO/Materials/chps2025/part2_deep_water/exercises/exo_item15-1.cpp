#include <iostream>

int main() {
    auto lambda = [](int i){return 2*i;};
    std::cout << "lambda(1)=" << lambda(1) << std::endl;
    int i = 1;
    auto lambda2 = [i] {return 2*i;};
    std::cout << "lambda2()=" << lambda2() << std::endl;
    auto lambda3 = [&i] {i*=2;};
    lambda3();
    std::cout << "i = " << i <<  std::endl;
    return 0;
}