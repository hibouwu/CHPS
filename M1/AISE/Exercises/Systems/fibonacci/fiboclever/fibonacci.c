#include "fibonacci.h"

const char * which_fibonacci = "Clever Fibonacci";

long long int fibonacci(int n) {
  if(n < 2) {
    return n;
  }
  long long int x = 0, y = 1, t;
  for(int i = 2; i <= n; i++) {
    t = y;
    y = x + y;
    x = t;
  }
  return y;
}
