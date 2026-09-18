/**
 * @file basic-sum-two-waits.c
 * @brief Sums up four integers.
 *
 * This is a test program for the ExPResSO library. It has a reference
 * sequential as well as a parallel implementation using ExPResSO.
 *
 * This program does not expect any argument.
 */

#include <stdio.h>
#include "expresso.h"

/**
 * @var struct s_data
 * @brief Structure for passing data to parallelizable tasks.
 */
struct s_data {
  int a, b;
};

/**
 * @fn void basic_sum_task(void * data)
 * @brief The work to do by a parallelizable task using @a data.
 */
void basic_sum_task(void * data) {
  struct s_data * this = (struct s_data *) data;
  this->a += this->b;
}

/**
 * @fn int main(void)
 * @brief Main function.
 */
int main(void) {
  int a = 10, b = 11, c = 7, d = 14;
  int reference, expresso;

  // Reference sequential implementation.
  reference = a + b + c + d;

  // Parallel implementation using ExPResSO.
  struct s_data * data = (struct s_data *) malloc(2 * sizeof(struct s_data));
  expresso_initialize();
  // The first task does `a = a + b'.
  data[0].a = a;
  data[0].b = b;
  expresso_task(&basic_sum_task, (void *) &data[0]);
  // The second task does `c = c + d'.
  data[1].a = c;
  data[1].b = d;
  expresso_task(&basic_sum_task, (void *) &data[1]);
  expresso_wait();
  // The third task reuses the results from the first two tasks and computes the
  // final sum.
  data[0].b = data[1].a;
  expresso_task(&basic_sum_task, (void *) &data[0]);
  expresso_wait();
  // Retrieve the final sum.
  expresso = data[0].a;
  expresso_stats();
  expresso_finalize();

  printf("Reference result: %d\n", reference);
  printf(" ExPResSO result: %d\n", expresso);

  // Results check.
  if(reference != expresso) {
    fprintf(stderr, "Bad results :-(\n");
    free(data);
    return 1;
  }

  printf("Good results :-)\n");
  free(data);
  return 0;
}
