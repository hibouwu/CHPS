#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <pthread.h>
#include <assert.h>

#define N 10

double arraymax_ref(size_t n, double a[n]);


/* ARRAYMAX */
// (modify this function)

/**
 * @brief Structure pour stocker les données et les mutex des threads
 */
typedef struct {
  double value;
  double *max;
  pthread_mutex_t *mutex;
} element_t;

/**
 * @brief Fonction exécutée par chaque thread
 */
void *check_max(void *arg) {
  element_t *val = (element_t *)arg;
  // Verrouiller le mutex
  pthread_mutex_lock(val->mutex);
  if (val->value > *(val->max)) {*(val->max) = val->value;}
  pthread_mutex_unlock(val->mutex);
  pthread_exit(NULL);
}

/**
 * @brief Fonction principale pour calculer le maximum d'un tableau
 */
double arraymax_par1(size_t n, double a[n]) {
  if(n == 0) return 0.;
  double max = a[0];
  // Initialiser le mutex
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);
  // Initialiser et créer les threads
  pthread_t threadsID[n-1]; // comme le premier element est déjà dans max, on en a besoin que de n-1
  element_t elements[n-1];
  for(size_t i=1; i<n; ++i) {
    elements[i-1].value = a[i];
    elements[i-1].max = &max;
    elements[i-1].mutex = &mutex;
    pthread_create(&threadsID[i-1], NULL, check_max, (void *)&elements[i-1]);
  }
  // Barriere : attendre la fin de tous les threads
  for(size_t i=0; i<n-1; ++i) {pthread_join(threadsID[i], NULL);}
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
  double res = arraymax_par1(n, a);
  
  printf("\nref=%lf res=%lf\n", ref, res);
  if(isClose(ref, res, 0.0001)) {
    printf("OK\n");
  }
  else {
    printf("ERROR: difference between ref and res is above threshold\n");
  }

  return 0;
}
