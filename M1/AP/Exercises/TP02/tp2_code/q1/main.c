#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define REPETS 100
#define N 1000

// RDTSC returns the time stamp counter (TSC), increased at every clock cycle
// It allows for very fine-grain (almost cycle accurate) time measurements
inline __attribute__((always_inline)) unsigned long long int rdtsc() {
  unsigned long long int a, d;
  __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
  return (d<<32) | a;
}


double benchmark(double a[N], void (*f)(size_t, double[N])) {
  unsigned long long start, stop, t;
  
  t = 0;
  for(unsigned i=0; i<REPETS; ++i) {
    for(size_t j=0; j<N; ++j) {
      a[j] = (double) j;
    }

    start = rdtsc();
    (*f)(N, a);
    stop = rdtsc();
    t += stop - start;
  }

  return (double) t / (double) REPETS / (double) N;
}

/**********************/


void loop_asm(size_t n, double a[n]);
void loop_asm_opt(size_t n, double a[n]);


void loop(size_t n, double a[n]) {
  for(size_t i=0; i<n-1; ++i) {
    a[i] = a[i+1] / sqrt(2.);
  }
}


int main(void) {

  double a_ref[N], a[N], a_opt[N];

  for(size_t i=0; i<N; ++i) {
    a_ref[i] = (double) i;
  }
  loop(N, a_ref);

  double t = benchmark(a, loop_asm);
  double t_opt = benchmark(a_opt, loop_asm_opt);
 
  for(size_t i=0; i<5; ++i) {
    printf(
      "a_ref[%d]=%lf  a[%d]=%lf a_opt[%d]=%lf\n", 
      i, a_ref[i], i, a[i], i, a_opt[i]
    );
  }
  for(size_t i=N-5; i<N; ++i) {
    printf(
      "a_ref[%d]=%lf  a[%d]=%lf a_opt[%d]=%lf\n", 
      i, a_ref[i], i, a[i], i, a_opt[i]
    );
  }

  printf("t=%lf t_opt=%lf\n", t, t_opt);

  return 0;
}
