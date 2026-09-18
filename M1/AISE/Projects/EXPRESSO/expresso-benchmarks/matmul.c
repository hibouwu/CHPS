/**
 * @file matmul.c
 * @brief Computes the product of two matrices.
 *
 * This is a benchmark program for the ExPResSO library. It has a reference
 * sequential and a room for a parallel implementation using ExPResSO.
 *
 * This program accepts exactly four optional arguments:
 *   1. dimensions (N, K and M) of the operands and the result,
 *   2. number of rows of the first operand N to process by each parallelizable
 *      task.
 *
 * The fourth argument is applicable only to the parallel implementation.
 */

#include <stdio.h>
#include <stdlib.h>
#include "expresso.h"

// Forward declaration
void matmul_product(size_t n, size_t k, size_t m, double * a, double * b, double * c);

struct matmul_data {
    size_t n, k, m;
    double *a, *b, *c;
};

void matmul_task(void *arg) {
    struct matmul_data *data = (struct matmul_data *)arg;
    matmul_product(data->n, data->k, data->m, data->a, data->b, data->c);
}

/**
 * @fn void matmul_initialize(size_t n, size_t k, size_t m, double * a, double * b)
 * @brief Initializes matrices with arbitrary values.
 *
 * Initializes the matrix @a a of size @a n times @a k as well as the matrix @a
 * b of size @a k times @a m with arbitrary values.
 */
void matmul_initialize(size_t n, size_t k, size_t m, double * a, double * b) {
  for(size_t i = 0; i < n; i++)
    for(size_t j = 0; j < k; j++)
      a[i * k + j] = i + j;	
  for(size_t i = 0; i < k; i++)
    for(size_t j = 0; j < m; j++)
      b[i * m + j] = i + j;
}

/**
 * @fn void matmul_product(size_t n, size_t k, size_t m, double * a, double * b, double * c)
 * @brief Multiplies two matrices and stores the result in a third matrix.
 *
 * Multiplies the matrix @a a of size @a n times @a k by the matrix @a b of size
 * @a k times @a m and stores the result in the matrix @a c of size @a n times
 * @a m.
 */
void matmul_product(
  size_t n, size_t k, size_t m, double * a, double * b, double * c
) {
  for(size_t x = 0; x < n; x++) {
    for(size_t y = 0; y < m; y++) {
      double temp = 0.;			
      for(size_t z = 0; z < k; z++) {
        temp += a[x * k + z] * b[z * m + y];
      }
      c[x * m + y] = temp;
    }
  }
}

/**
 * @fn int matmul_check(size_t n, size_t m, double * r, double * e)
 * @brief Checks the equality of two matrices.
 *
 * Verifies whether the matrix @a r of size @a n times @a m and the matrix @a e
 * of size @a n times @a m have the same coefficients.
 *
 * @returns 0 if @a r has the same coefficients as @a e
 * @returns 1 otherwise
 */
int matmul_check(size_t n, size_t m, double * r, double * e) {
  for(size_t i = 0; i < n; i++)
    for(size_t j = 0; j < m; j++)
      if(r[i * m + j] != e[i * m + j])
        return 1;
  return 0;
}

/**
 * @fn int main(int argc, char ** argv)
 * @arg argc Number of command-line arguments (including the executable name).
 * @arg argv Values of command-line arguments (including the executable name).
 * @brief Main function.
 */
int main(int argc, char ** argv) {
  size_t n = 32, k = 32, m = 32, row_block = 8;
  if(argc > 1 && argc < 5) {
    fprintf(
      stderr,
      "Missing arguments!\n"
      "\n"
      "Usage: %s N K M L\n\n"
      "Multiply a matrix A of size NxK by a matrix B of size KxM and store the "
      "result in a matrix C of size NxM. In parallel, assign the computation "
      "of blocks of L rows of C to each parallelizable task.\n",
      argv[0]
    );
    return 1;
  }
  if(argc > 4) {
    n = strtoull(argv[1], 0, 0);
    k = strtoull(argv[2], 0, 0);
    m = strtoull(argv[3], 0, 0);
    row_block = strtoull(argv[4], 0, 0);
  }
  if(n < 2) {
    n = 2;
  }
  if(k < 2) {
    k = 2;
  }
  if(m < 2) {
    m = 2;
  }
  if(row_block > n) {
    row_block = n;
  }
  
  double * a = malloc(n * k * sizeof(double));
  double * b = malloc(k * m * sizeof(double));
  double * c_reference = calloc(n * m, sizeof(double));
  double * c_expresso = calloc(n * m, sizeof(double));
  double time_reference = 0.0, time_expresso = 0.0;

  // Initialization with arbitrary values.
  matmul_initialize(n, k, m, a, b);

  // Reference sequential implementation.
  time_reference = expresso_wall_time();
  matmul_product(n, k, m, a, b, c_reference);
  time_reference = expresso_wall_time() - time_reference;

  // Parallel implementation using ExPResSO.
  expresso_initialize();
  
  // Partitionnement par row_block, découpage le long de la dimension N
  int num_blocks = (n + row_block - 1) / row_block;
  struct matmul_data *data = malloc(sizeof(struct matmul_data) * num_blocks);
  for (int i = 0; i < num_blocks; i++) {
      size_t start_row = i * row_block;
      size_t end_row = start_row + row_block;
      if (end_row > n) end_row = n;
      size_t current_rows = end_row - start_row;
      
      data[i].n = current_rows;
      data[i].k = k;
      data[i].m = m;
      
      data[i].a = &a[start_row * k];
      data[i].b = b;
      data[i].c = &c_expresso[start_row * m];
  }

  time_expresso = expresso_wall_time();

  for (int i = 0; i < num_blocks; i++) {
      // Estimation du poids : nb lignes * K * M (charge de calcul)
      unsigned int weight = data[i].n * data[i].k * data[i].m;
      expresso_weighted_task(matmul_task, &data[i], weight);
  }

  expresso_wait();
  time_expresso = expresso_wall_time() - time_expresso;
  
  expresso_stats();
  expresso_finalize();
  free(data);
  /*** fin ***/

  // Print results.
  if(n <= 16 && m <= 16) {
    printf("Reference result:\n");
    for(size_t i = 0; i < n; i++) {
      for(size_t j = 0; j < m; j++)
        printf(" %.2f ", c_reference[i * m + j]);
      printf("\n");
    }
    printf("\n");
    printf(" ExPResSO result:\n");
    for(size_t i = 0; i < n; i++) {
      for(size_t j = 0; j < m; j++)
        printf(" %.2f ", c_expresso[i * m + j]);
      printf("\n");
    }
    printf("\n");
  }

  // Results check.
  if(matmul_check(n, m, c_reference, c_expresso)) {
    fprintf(stderr, "Bad results :-(\n");
    free(a); free(b); free(c_reference); free(c_expresso);
    return 1;
  }

  printf("Reference computation time: %g s\n", time_reference);
  printf(" ExPResSO computation time: %g s\n", time_expresso);

  printf("Good results :-)\n");
  free(a); free(b); free(c_reference); free(c_expresso);
  return 0;
}
