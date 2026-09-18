#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fibonacci.h>

int main(int argc, char ** argv) {
  int n = 20;
  if(argc > 1) {
    int a = atoi(argv[1]);
    if(a > 0) {
      n = a;
    }
  }
  
  printf("Implémentation : %s\n", which_fibonacci);

  long long int r;
  time_t begin = time(NULL), end;
  r = fibonacci(n);
  end = time(NULL);

  printf("Fibonacci(%d) : %lld\n", n, r);
  printf("Temps de calcul : %g s\n", difftime(end, begin));

  return 0;
}
