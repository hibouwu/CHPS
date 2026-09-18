#include <iostream>

void print_while(int start, int end) {
    std::cout << "print while " << start << " to " << end << std::endl;
    int i = start;
    while (i <= end) {
        std::cout << i << std::endl;
        ++i;
    }
}