#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define M 9
#define N 7


void transpose_scalar(size_t m, size_t n, double a[m][n], double b[n][m]);
void transpose_vector(size_t m, size_t n, double a[m][n], double b[n][m]);

void transpose(size_t m, size_t n, double a[m][n], double b[n][m]) {
for(size_t i=0; i<N; ++i) {
    for(size_t j=0; j<M; ++j) {
      b[i][j] = a[j][i];
    }
  }
}


void print_matrix(size_t m, size_t n, double a[m][n]) {
  for(size_t i=0; i<m; ++i) {
    for(size_t j=0; j<n; ++j) {
      printf(" %.2lf ", a[i][j]);
    }
    printf("\n");
  }
}


int main(void) {

  double a[M][N];
  double b_ref[N][M];
  double b_scalar[N][M];
  double b_vector[N][M];

  // Init a
  for(uint64_t i=0; i<M; i++) {
    for(uint64_t j=0; j<N; j++) {
      a[i][j] = (double) (i*N + j);
      b_ref[j][i] = (double) -1.;
      b_scalar[j][i] = (double) -1.;
      b_vector[j][i] = (double) -1.;
    }
  }

  transpose(M, N, a, b_ref);
  transpose_scalar(M, N, a, b_scalar);
  transpose_vector(M, N, a, b_vector);

  printf("a=\n");
  print_matrix(M, N, a);

  printf("b_ref=\n");
  print_matrix(N, M, b_ref);

  printf("b_scalar=\n");
  print_matrix(N, M, b_scalar);
  
  printf("b_vector=\n");
  print_matrix(N, M, b_vector);

  return 0;
}
