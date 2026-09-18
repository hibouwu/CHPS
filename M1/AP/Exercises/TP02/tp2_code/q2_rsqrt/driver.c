#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variants.h"
#include "benchmarks.h"


/*
 * Inputs generation
 */

void gen_inputs(float x_single[2800], double x_double[2800]) {
  /*
   * Generate an input array comprised of the following sections:
   * - ]0, 10] with steps 0.01
   * - [10, 100] with steps 0.1
   * - [100, 1000] with steps 1
   * Note that the array is generated in both single and double precision versions
   */
  
  unsigned i = 0;
  
  double step = 0.01;
  double current = step;
  while(current < 10.) {
    x_single[i] = (float) current;
    x_double[i] = current;
    current += step;
    i++;
  }
  
  step = 0.1;
  while(current < 100.) {
    x_single[i] = (float) current;
    x_double[i] = current;
    current += step;
    i++;
  }
  
  step = 1.;
  while(current < 1000.) {
    x_single[i] = (float) current;
    x_double[i] = current;
    current += step;
    i++;
  }
}


/*
 * Reference computation in double-precision
 */

double ref(double x) {
  double y = 1.;
  asm(
    "sqrtsd %0, %1;"
    : "+x" (y)
    : "x" (x)
    :
  );
  return 1. / y;
}


void compute_ref(size_t n, double x[n], double y[n]) {
  for(size_t i=0; i<n; ++i) {
    y[i] = ref(x[i]);
  }
}


/*
 * Errors computation & export to .dat
 */

void compute_errors(size_t n, double ref[n], float y[n], double e_abs[n], double e_rel[n]) {
  // ref: array of reference values, double precision
  // y: array of tested values, single precision
  // e_abs: array of absolute errors
  // e_rel: array of relative errors

  for(size_t i=0; i<n; ++i) {
    e_abs[i] = ref[i] - ((double) y[i]);
    e_rel[i] = (ref[i] - ((double) y[i])) / ref[i];
  }
}


void dump_results(
  char *path, size_t n, 
  double x_double[n], double y_double[n], float y_single[n],
  double e_abs[n], double e_rel[n]
) {
  FILE *fptr;
  fptr = fopen(path, "w");
  
  fprintf(fptr, "# x y_double y_float e_abs e_rel\n");
  for(size_t i=0; i<n; ++i) {
    fprintf(
      fptr, "%.15lf %.15lf %.15lf %.15lf %.15lf\n", 
      x_double[i], y_double[i], y_single[i], e_abs[i], e_rel[i]
    );
  }

  fclose(fptr);
  printf("Wrote results to %s\n", path);
}


/* main */

int main(int argc, void **argv) {

  if(argc != 2) {
    printf("Error: Incorrect usage, should be:\n./driver [alg]\nWhere alg is: naive, newton, fast\n");
    return 1;
  }
  char *alg = (char*) argv[1];

  size_t n = 2800;
  float x_single[n]; double x_double[n];
  float y_single[n]; double y_double[n];
  gen_inputs(x_single, x_double);
  double t;
  char res_out[100]; //char err_out[100];

  if(strcmp(alg, "naive") == 0) {
    printf("naive\n");
    t = benchmark_naive(n, x_single, y_single);
    strcpy(res_out, "outputs/naive_results.dat");
  }

  else if(strcmp(alg, "newton") == 0) {
    printf("newton\n");
    // Only going as far as x=10 because we use y=1 as guess
    n = 1000;
    t = benchmark_newton(n, x_single, y_single);
    strcpy(res_out, "outputs/newton_results.dat");
  }

  else if(strcmp(alg, "fast") == 0) {
    printf("fast\n");
    t = benchmark_fast(n, x_single, y_single);
    strcpy(res_out, "outputs/fast_results.dat");
  }

  else {
    printf("Error: %s is not a valid algorithm variant (naive, newton, fast)\n", alg);
    return 1;
  }

  // Print cycles to std output, compute FP64 reference, error, and dump result file
  printf("Cycles/iter: %lf\n", t);
  double e_abs[n]; double e_rel[n];
  compute_ref(n, x_double, y_double);
  compute_errors(n, y_double, y_single, e_abs, e_rel);
  dump_results(res_out, n, x_double, y_double, y_single, e_abs, e_rel);
  // dump_errors(err_out, n, x_double, e_abs, e_rel);

  return 0;
}
