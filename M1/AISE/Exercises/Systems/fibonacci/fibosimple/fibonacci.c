#include "fibonacci.h"

const char * which_fibonacci = "Simple Fibonacci";

long long int fibonacci(int n) {
  if(n < 2) {
    return n;
  }
  return fibonacci(n - 1) + fibonacci(n - 2);
}
