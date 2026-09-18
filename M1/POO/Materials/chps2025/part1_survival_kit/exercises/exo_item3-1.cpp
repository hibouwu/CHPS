#include <iostream>
int main()
{
    int n = 1;
    int m = (++n, n+=2, 2 * n);
    std::cout << "m = " << (++m, m) << '\n'; // m = 9
}
