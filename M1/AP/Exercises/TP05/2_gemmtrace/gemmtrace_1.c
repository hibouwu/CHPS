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

/**
 * @brief Structure pour stocker les indices et les matrices pour chaque thread
 */
typedef struct {
  size_t index;
  size_t n;
  double *a;
  double *b;
  double *res;
  pthread_mutex_t *mutex;
} element_t;

/**
 * @brief Fonction exécutée par chaque thread pour calculer un élément diagonal
 */
void *compute_diag(void *arg) {
  element_t *el = (element_t *)arg;
  double dot_prod = 0.0;
  size_t n = el->n;
  size_t i = el->index;

  // Calcul du produit scalaire pour c_ii
  for (size_t k = 0; k < n; ++k) {
    // a[i][k] * b[k][i]
    // En convertissant les tableaux 2D en pointeurs plats
    dot_prod += el->a[i * n + k] * el->b[k * n + i];
  }

  // Verrouiller le mutex et mettre à jour le résultat global
  pthread_mutex_lock(el->mutex);
  *(el->res) += dot_prod;
  pthread_mutex_unlock(el->mutex);

  pthread_exit(NULL);
}

double gemmtrace_par1(size_t n, double a[n][n], double b[n][n]) {
  double res = 0.;

  // Initialiser le mutex
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);

  // Initialiser et créer les threads
  pthread_t threads[n];
  element_t elements[n];

  for(size_t i=0; i<n; ++i) {
    elements[i].index = i; // c_ii
    elements[i].n = n;     // taille de la matrice
    elements[i].a = (double *)a; // la pointer 1D de matrice a
    elements[i].b = (double *)b; // la pointer 1D de matrice b
    elements[i].res = &res;
    elements[i].mutex = &mutex;

    pthread_create(&threads[i], NULL, compute_diag, (void *)&elements[i]);
  }

  // Barriere : attendre la fin de tous les threads
  for(size_t i=0; i<n; ++i) {
    pthread_join(threads[i], NULL);
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
  double res = gemmtrace_par1(n, A, B);
  
  printf("\nref=%lf res=%lf\n", ref, res);
  if(isClose(ref, res, 0.0001)) {
    printf("OK\n");
  }
  else {
    printf("ERROR: difference between ref and res is above threshold\n");
  }

  return 0;
}
