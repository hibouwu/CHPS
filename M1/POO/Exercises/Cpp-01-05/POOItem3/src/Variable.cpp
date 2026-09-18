#include <iostream>

int main(){
    bool  a = true;
    int   b(1); 
    float c{3.14}; // initialisation uniforme recommandée ; plus robuste

    int n = 1;
    int m = (++n, n+=2, 2 * n);
    std::cout << "m = " << (++m, m) << '\n';
    //m = 9

    int i = 1 + 2 + 3 + 4; //(((1+2)+3)+4)
    int j = 1 + 2 * 3 + 4; // (1+(2*3)+4)

    bool b = true && false && true; // ((true && false) && true)
    bool c = true || false && true; // (true || (false && true))

    int k;
    i = j = k = 0; // i = (j = (k = 0))


    return 0;
}