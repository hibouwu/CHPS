#include <stddef.h>
#include <stdio.h>

double gemmtrace_ref(size_t n, double a[n][n], double b[n][n]) {
  double res = 0.;

  for(size_t i=0; i<n; ++i) {
    for(size_t j=0; j<n; ++j) {
        res += a[i][j] * b[j][i];
    }
  }

  return res;
}
