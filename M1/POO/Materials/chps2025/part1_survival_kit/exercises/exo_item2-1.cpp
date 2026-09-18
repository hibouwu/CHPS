#include <iostream>

int nb_iterations = 101;

int main() {        

    // Print integer 
    for (int i = 0 ; i < nb_iterations; i++) {
        std::cout << "integer i =  " << i << "\n";
    }

    // Print even integer
    for (int i = 0 ; i < nb_iterations; i++) {
        if (i%2 ==0) {
            std::cout << "even integer  i =  " << i << "\n";
        }
    }

    // Print odd integer
    for (int i = 0 ; i < nb_iterations; i++) {
        if (bool is_odd = (i%2 !=0); is_odd) {
            std::cout << "odd integer  i =  " << i << "\n";
        }
    }

    // Print 5 or 2 multiple
    for (int i = 0 ; i < nb_iterations; i++) {
        if (i%5 ==0) {
            std::cout << "5 multiple  i =  " << i << "\n";
        }
        else if (i%2==0) { 
            std::cout << "2 multiple i = " << i << "\n";
        }
        else {
            std::cout << "nor 5 neither 2 multiple i = " << i << "\n";
        }
    }
    return 0;

}
