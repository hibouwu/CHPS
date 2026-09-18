#include <stddef.h>
#include <stdio.h>

#include "variants.h"

#define WARMUPS 100
#define REPETS 100000


// RDTSC returns the time stamp counter (TSC), increased at every clock cycle
// It allows for very fine-grain (almost cycle accurate) time measurements
inline __attribute__((always_inline)) unsigned long long int rdtsc() {
  unsigned long long int a, d;
  __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
  return (d<<32) | a;
}


double benchmark_naive(size_t n, float x[n], float r[n]) {
  unsigned warmups = WARMUPS;
  unsigned repets = REPETS;
  unsigned long long t_acc = 0;

  naive(n, x, r, warmups);
 
  unsigned long long start = rdtsc();
  naive(n, x, r, repets);
  unsigned long long stop = rdtsc();

  double time = (double) (stop - start);
  double time_iter = time / ( (double) repets*n);

  return time_iter;
}


double benchmark_newton(size_t n, float x[n], float r[n]) {
  unsigned warmups = WARMUPS;
  unsigned repets = REPETS;
  unsigned long long t_acc = 0;
  
  float guess = 1.;

  newton(n, x, guess, r, warmups);
 
  unsigned long long start = rdtsc();
  newton(n, x, guess, r, repets);
  unsigned long long stop = rdtsc();

  double time = (double) (stop - start);
  double time_iter = time / ( (double) repets*n);

  return time_iter;
}


double benchmark_fast(size_t n, float x[n], float r[n]) {
  unsigned warmups = WARMUPS;
  unsigned repets = REPETS;
  unsigned long long t_acc = 0;

  fast(n, x, r, warmups);
 
  unsigned long long start = rdtsc();
  fast(n, x, r, repets);
  unsigned long long stop = rdtsc();

  double time = (double) (stop - start);
  double time_iter = time / ( (double) repets*n);

  return time_iter;
}
