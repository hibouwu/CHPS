/**
 * @file dot.c
 * @brief Computes the dot product of two vectors.
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

struct dot_data {
    double *v1;
    double *v2;
    int size;
    double partial_sum;
};

void dot_product_task(void *arg) {
    struct dot_data *data = (struct dot_data *)arg;
    data->partial_sum = 0.0;
    for (int i = 0; i < data->size; i++) {
        data->partial_sum += data->v1[i] * data->v2[i];
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
  
  double * v1 = (double *) malloc((size_t) size * sizeof(double)),
         * v2 = (double *) malloc((size_t) size * sizeof(double));
  double sum_reference = 0.0, sum_expresso = 0.0;
  double time_reference = 0.0, time_expresso = 0.0;

  // Initialization with random values.
  for(int i = 0; i < size; i++) {
    v1[i] = rand() % 10;
    v2[i] = rand() % 10;
  }

  // Reference sequential implementation.
  time_reference = expresso_wall_time();
  for(int i = 0; i < size; i++) {
    sum_reference += v1[i] * v2[i];
  }
  time_reference = expresso_wall_time() - time_reference;

  // Parallel implementation using ExPResSO.
  expresso_initialize();
  
  int num_blocks = (size + block - 1) / block;
  struct dot_data *ddata = malloc(sizeof(struct dot_data) * num_blocks);
  for (int i = 0; i < num_blocks; i++) {
      int start = i * block;
      int end = start + block;
      if (end > size) end = size;
      
      ddata[i].v1 = &v1[start];
      ddata[i].v2 = &v2[start];
      ddata[i].size = end - start;
      ddata[i].partial_sum = 0.0;
  }

  time_expresso = expresso_wall_time();

  for (int i = 0; i < num_blocks; i++) {
        expresso_task(dot_product_task, &ddata[i]);
  }
  
  expresso_wait();
  
  for (int i = 0; i < num_blocks; i++) {
      sum_expresso += ddata[i].partial_sum;
  }

  time_expresso = expresso_wall_time() - time_expresso;
  
  expresso_stats();
  expresso_finalize();
  free(ddata);
  /****** fin ******/

  printf("Reference result: %g\n", sum_reference);
  printf(" ExPResSO result: %g\n", sum_expresso);

  // Results check.
  if(sum_reference != sum_expresso) {
    fprintf(stderr, "Bad results :-(\n");
    free(v1); free(v2);
    return 1;
  }

  printf("Reference computation time: %g s\n", time_reference);
  printf(" ExPResSO computation time: %g s\n", time_expresso);

  printf("Good results :-)\n");
  free(v1); free(v2);
  return 0;
}
