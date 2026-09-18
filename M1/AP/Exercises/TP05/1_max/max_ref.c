#include <stddef.h>

double arraymax_ref(size_t n, double a[n]) {
  if(n == 0) return 0.;
  double max = a[0];

  for(size_t i=1; i<n; ++i) {
    if(a[i] > max) {
      max = a[i];
    }
  }

  return max;
}
