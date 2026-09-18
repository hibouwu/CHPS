#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


void transpose_scalar(size_t m, size_t n, double a[m][n], double b[n][m]) {

  asm(
    ""
    :
    : [m]"r"(m), [n]"r"(n), [a]"r"(a), [b]"r"(b)
    : 
  );
}


void transpose_vector(size_t m, size_t n, double a[m][n], double b[n][m]) {
  uint64_t mask;
  uint64_t *maskptr = &mask;
  uint64_t indices[4] = {0, n, n*2, n*3};
  printf("indices = %lu %lu %lu %lu\n", indices[0], indices[1], indices[2],indices[3]);

  asm(
    ""
    :
    : [m]"r"(m), [n]"r"(n), [a]"r"(a), [b]"r"(b), [mask]"r"(maskptr), [indices]"r"(indices)
    : 
  );
}
