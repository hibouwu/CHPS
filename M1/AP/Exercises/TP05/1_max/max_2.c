#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <pthread.h>
#include <assert.h>

#define N 12

double arraymax_ref(size_t n, double a[n]);


/* ARRAYMAX */
// (modify this function)

#define K 3  // taille des blocs

/**
 * @brief Structure pour stocker les données et les mutex des threads
 */
typedef struct {
  double *array_start;
  size_t size;
  double *max;
  pthread_mutex_t *mutex;
} block_t;

/**
 * @brief Fonction exécutée par chaque thread
 */
void *block_max(void *arg) {
  block_t *val = (block_t *)arg;
  double local_max = -INFINITY;
  printf("val->size=%zu\n", val->size);
  if (val->size > 0) {
    local_max = val->array_start[0];
    for (size_t i = 1; i < val->size; ++i) {
      if (val->array_start[i] > local_max) { local_max = val->array_start[i]; }
    }
  }
  // Verrouiller le mutex
  pthread_mutex_lock(val->mutex);
  if (local_max > *(val->max)) { *(val->max) = local_max; }
  pthread_mutex_unlock(val->mutex);
  pthread_exit(NULL);
}

/**
 * @brief Fonction principale pour calculer le maximum d'un tableau
 */
double arraymax_par2(size_t n, double a[n]) {
  if(n == 0) return 0.;
  double max = a[0]; 

  // Initialiser le mutex
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);

  size_t num_threads = n / K;
  
  // Initialiser les threads
  pthread_t threadsID[num_threads];
  block_t blocks[num_threads];

  // Créer les threads
  for(int i=0; i<num_threads; ++i) {
    size_t start_index = i * K;
    // Le dernier thread traite les éléments restants si n % K != 0
    size_t current_block_size = (i == num_threads - 1) ? (n - start_index) : K;
    
    blocks[i].array_start = &a[start_index];
    blocks[i].size = current_block_size;
    blocks[i].max = &max;
    blocks[i].mutex = &mutex;
    
    pthread_create(&threadsID[i], NULL, block_max, (void *)&blocks[i]);
  }

  // Barriere : attendre la fin de tous les threads
  for(int i=0; i<num_threads; ++i) { pthread_join(threadsID[i], NULL); }

  // Detruire le mutex
  pthread_mutex_destroy(&mutex);

  return max;
}


/* UTILS */

void initArray(size_t n, double a[n]) {
  static double elem = 0.;
  for(size_t i=0; i<n; ++i) {
    a[i] = elem;
    elem += 1.;
  }
}

void printArray(size_t n, double a[n]) {
  for(size_t i=0; i<n; ++i) {
    printf("%lf ", a[i]);
  }
  printf("\n");
}

inline bool isClose(double a, double b, double threshold) {
  return fabs(a - b) < threshold;
}


/* MAIN */

int main(void) {
  size_t n = N;

  double a[n];
  initArray(n, a);
  a[2] = 12.;
  a[3] = -12.;

  printf("a=\n");
  printArray(n, a);

  double ref = arraymax_ref(n, a);
  double res = arraymax_par2(n, a);
  
  printf("\nref=%lf res=%lf\n", ref, res);
  if(isClose(ref, res, 0.0001)) {
    printf("OK\n");
  }
  else {
    printf("ERROR: difference between ref and res is above threshold\n");
  }

  return 0;
}
