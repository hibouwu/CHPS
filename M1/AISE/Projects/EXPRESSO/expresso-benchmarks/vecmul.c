/**
 * @file vecmul.c
 * @brief Computes the element-wise product of two vectors.
 *
 * This is a benchmark program for the ExPResSO library. It has a reference
 * sequential and a room for a parallel implementation using ExPResSO.
 *
 * This program accepts exactly two optional arguments:
 *   1. size of the vectors,
 *   2. number of elements of the vectors processed by each parallelizable task.
 *
 * The second argument is applicable only to the parallel implementation.
 */

#include <stdio.h>
#include <stdlib.h>
#include "expresso.h"

struct vecmul_data {
    double *v1;
    double *v2;
    int size;
};

void vecmul_task(void *arg) {
    struct vecmul_data *data = (struct vecmul_data *)arg;
    for (int i = 0; i < data->size; i++) {
        data->v1[i] *= data->v2[i];
    }
}

/**
 * @fn int main(int argc, char ** argv)
 * @arg argc Number of command-line arguments (including the executable name).
 * @arg argv Values of command-line arguments (including the executable name).
 * @brief Main function.
 */
int main(int argc, char ** argv) {
  int size = 1024, block = 64;
  if(argc == 2) {
    fprintf(stderr, "Missing block size!\n");
    return 1;
  }
  if(argc > 2) {
    size = atoi(argv[1]);
    block = atoi(argv[2]);
  }
  if(block > size) {
    block = size;
  }
  
  double * rv1 = (double *) malloc((size_t) size * sizeof(double)),
         * rv2 = (double *) malloc((size_t) size * sizeof(double));
  double * ev1 = (double *) malloc((size_t) size * sizeof(double)),
         * ev2 = (double *) malloc((size_t) size * sizeof(double));
  double time_reference = 0.0, time_expresso = 0.0;

  // Initialization with random values.
  for(int i = 0; i < size; i++) {
    rv1[i] = rand() % 10;
    rv2[i] = rand() % 10;
    ev1[i] = rv1[i];
    ev2[i] = rv2[i];
  }

  // Reference sequential implementation.
  time_reference = expresso_wall_time();
  for(int i = 0; i < size; i++) {
    rv1[i] *= rv2[i];
  }
  time_reference = expresso_wall_time() - time_reference;

  // Parallel implementation using ExPResSO.
  expresso_initialize();

  int num_blocks = (size + block - 1) / block;
  struct vecmul_data *ddata = malloc(sizeof(struct vecmul_data) * num_blocks);
  for (int i = 0; i < num_blocks; i++) {
      int start = i * block;
      int end = start + block;
      if (end > size) end = size;
      
      ddata[i].v1 = &ev1[start];
      ddata[i].v2 = &ev2[start];
      ddata[i].size = end - start;
  }
  
  time_expresso = expresso_wall_time();

  for (int i = 0; i < num_blocks; i++) {
      expresso_weighted_task(vecmul_task, &ddata[i], ddata[i].size);
  }
  
  expresso_wait();
  time_expresso = expresso_wall_time() - time_expresso;
  
  expresso_stats();
  expresso_finalize();
  free(ddata);
  /**** fin ***/

  // Print results.
  if(size <= 32) {
    printf("Reference result: [ ");
    for(int i = 0; i < size; i++)
      printf(" %.2lf ", rv1[i]);
    printf("]\n");
    printf(" ExPResSO result: [ ");
    for(int i = 0; i < size; i++)
      printf(" %.2lf ", ev1[i]);
    printf("]\n");
  }

  // Results check.
  for(int i = 0; i < size; i++) {
    if(rv1[i] != ev1[i]) {
      fprintf(stderr, "Bad results :-(\n");
      free(rv1); free(rv2); free(ev1); free(ev2);
      return 1;
    }
  }

  printf("Reference computation time: %g s\n", time_reference);
  printf(" ExPResSO computation time: %g s\n", time_expresso);

  printf("Good results :-)\n");
  free(rv1); free(rv2); free(ev1); free(ev2);
  return 0;
}
