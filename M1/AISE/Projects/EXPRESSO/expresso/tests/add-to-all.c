/**
 * @file add-to-all.c
 * @brief Adds a constant to each value of an vector.
 *
 * This is a test program for the ExPResSO library. It has a reference
 * sequential as well as a parallel implementation using ExPResSO.
 *
 * This program accepts exactly two optional arguments:
 *   1. size of the vector,
 *   2. number of elements of the vector processed by each parallelizable task.
 *
 * The second argument is applicable only to the parallel implementation.
 */

#include <stdio.h>
#include <stdlib.h>
#include "expresso.h"

/**
 * @var struct s_data
 * @brief Structure for passing data to parallelizable tasks.
 */
struct s_data {
  double * vector;
  double constant;
  int size;
};

/**
 * @fn void add_to_all_task(void * data)
 * @brief The work to do by a parallelizable task using @a data.
 */
void add_to_all_task(void * data) {
  struct s_data * this = (struct s_data *) data;
  for(int i = 0; i < this->size; i++) {
    this->vector[i] += this->constant;
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
  
  double * reference = (double *) malloc((size_t) size * sizeof(double));
  double * expresso = (double *) malloc((size_t) size * sizeof(double));

  // Initialization with random values.
  for(int i = 0; i < size; i++) {
    reference[i] = rand() % 10;
    expresso[i] = reference[i];
  }
  int constant = rand() % 10;

  // Reference sequential implementation.
  for(int i = 0; i < size; i++) {
    reference[i] += constant;
  }

  // Parallel implementation using ExPResSO.
  int tasks = size / block + ((size % block) > 0);
  struct s_data * data = malloc(tasks * sizeof(struct s_data));
  
  expresso_initialize();
  for(int i = 0; i < tasks; i++) {
    // Each task adds the same constant to each element of the vector between
    // `expresso[i * block]' and `expresso[i * block + block]'. If the number of
    // elements is not a multiple of `block', the last submitted task processes
    // the remaining elements.
    data[i].vector = &expresso[i * block];
    data[i].constant = constant;
    data[i].size = (i == tasks - 1) ? (size - (i * block)) : block;
    expresso_task(&add_to_all_task, (void *) &data[i]);
  }
  expresso_wait();
  expresso_stats();
  expresso_finalize();

  if(size <= 32) {
    printf("Reference result: [ ");
    for(int i = 0; i < size; i++)
      printf(" %.2lf ", reference[i]);
    printf("]\n");
    printf(" ExPResSO result: [ ");
    for(int i = 0; i < size; i++)
      printf(" %.2lf ", expresso[i]);
    printf("]\n");
  }
  
  // Results check.
  for(int i = 0; i < size; i++) {
    if(reference[i] != expresso[i]) {
      fprintf(stderr, "Bad results :-(\n");
      free(reference); free(expresso); free(data);
      return 1;
    }
  }

  printf("Good results :-)\n");
  free(reference); free(expresso); free(data);
  return 0;
}
