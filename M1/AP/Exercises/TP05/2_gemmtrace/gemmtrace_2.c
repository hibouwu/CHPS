#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <pthread.h>
#include <assert.h>

#define N 4

double gemmtrace_ref(size_t n, double a[n][n], double b[n][n]);

/* GEMMTRACE */
// (modify this function below)

#define K 4

/**
 * @brief Structure pour stocker les indices et les matrices pour chaque bloc
 */
typedef struct {
  size_t start_index;
  size_t size;
  size_t n;
  double *a;
  double *b;
  double *res;
  pthread_mutex_t *mutex;
} block_t;

/**
 * @brief Fonction exécutée par chaque thread pour calculer une partie de la trace
 */
void *block_diag(void *arg) {
  block_t *blk = (block_t *)arg;
  double local_sum = 0.0;
  size_t n = blk->n;
  size_t start = blk->start_index;
  size_t end = start + blk->size;

  for (size_t i = start; i < end; ++i) {
    double dot_prod = 0.0;
    for (size_t k = 0; k < n; ++k) {
        dot_prod += blk->a[i * n + k] * blk->b[k * n + i];
    }
    local_sum += dot_prod;
  }

  // Verrouiller le mutex et mettre à jour le résultat global
  pthread_mutex_lock(blk->mutex);
  *(blk->res) += local_sum;
  pthread_mutex_unlock(blk->mutex);

  pthread_exit(NULL);
}

double gemmtrace_par2(size_t n, double a[n][n], double b[n][n]) {
  double res = 0.;

  // Initialiser le mutex
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);

  size_t num_threads = n / K;
  if (n % K != 0) { // If n is not perfectly divisible by K, we need one more thread for the remainder
      num_threads++;
  }
  if (num_threads == 0 && n > 0) { // Handle case where K > n but n > 0, so at least one thread is needed
      num_threads = 1;
  } else if (n == 0) { // Handle case where n is 0
      num_threads = 0;
  }


  // Initialiser les threads
  pthread_t threadsID[num_threads];
  block_t blocks[num_threads];

  // Créer les threads
  for(int i=0; i<num_threads; ++i) {
    size_t start_index = i * K;
    // Le dernier thread traite les éléments restants
    size_t current_block_size = (i == num_threads - 1) ? (n - start_index) : K;
    
    blocks[i].start_index = start_index;
    blocks[i].size = current_block_size;
    blocks[i].n = n;
    blocks[i].a = (double *)a;
    blocks[i].b = (double *)b;
    blocks[i].res = &res;
    blocks[i].mutex = &mutex;

    pthread_create(&threadsID[i], NULL, block_diag, (void *)&blocks[i]);
  }

  // Barriere : attendre la fin de tous les threads
  for(int i=0; i<num_threads; ++i) {
    pthread_join(threadsID[i], NULL);
  }

  // Detruire le mutex
  pthread_mutex_destroy(&mutex);

  return res;
}

/* UTILS */

void initMatrix(size_t m, size_t n, double A[m][n]) {
  static double elem = 0.;
  for(size_t i=0; i<m; ++i) {
    for(size_t j=0; j<n; ++j) {
      A[i][j] = elem;
      elem += 1.;
    }
  }
}

void printMatrix(size_t m, size_t n, double A[m][n]) {
  for(size_t i=0; i<m; ++i) {
    for(size_t j=0; j<n; ++j) {
      printf("%lf ", A[i][j]);
    }
    printf("\n");
  }
}

inline bool isClose(double a, double b, double threshold) {
  return fabs(a - b) < threshold;
}


/* MAIN */

int main(void) {
  size_t n = N;

  double A[n][n];
  initMatrix(n, n, A);

  double B[n][n];
  initMatrix(n, n, B);


  printf("A=\n");
  printMatrix(n, n, A);

  printf("B=\n");
  printMatrix(n, n, B);


  double ref = gemmtrace_ref(n, A, B);
  double res = gemmtrace_par2(n, A, B);
  
  printf("\nref=%lf res=%lf\n", ref, res);
  if(isClose(ref, res, 0.0001)) {
    printf("OK\n");
  }
  else {
    printf("ERROR: difference between ref and res is above threshold\n");
  }

  return 0;
}
