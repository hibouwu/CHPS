#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

#define gettime(t) clock_gettime(CLOCK_MONOTONIC_RAW, t)
#define get_sub_seconde(t) (1e-9*(double)t.tv_nsec)
/** return time in second
*/
double get_elapsedtime(void)
{
  struct timespec st;
  int err = gettime(&st);
  if (err !=0) return 0;
  return (double)st.tv_sec + get_sub_seconde(st);
}

void init(double* A, double* B, double* C, int size)
{
  int i = 0, j = 0;

	srand(2026);

	for(i = 0; i < size; i++)
  {
		for(j = 0; j < size; j++)
    {
			A[i * size + j] = i * 1.; // rand();
			B[i * size + j] = i * 1.; // rand()
			C[i * size + j] = 0.0;
		}
	}
}

void dgemm(int M, int N, int K, double alpha, const double *A, const double *B, double beta, double *C)
{
  int i = 0, j = 0, k = 0;

  for(i = 0; i < M; i++)
  {
    for(j = 0; j < N; j++)
    {
      double sum = 0.;
      for(k = 0; k < K; k++)
      {
        sum += A[i * K + k] * B[k * N + j];
      }
      C[i * N + j] = alpha * sum + beta * C[i * N + j];
    }
  }
}

int main(int argc, char** argv){
	int N;

	double *A;
	double *B;
	double *C;

	N = (argc < 2)?1024:atoi(argv[1]);
	fprintf(stdout, "Matrix Multiplication\n  Size: %dx%d\n", N, N);

	// Memory allocation
	A= (double*) malloc(sizeof(double) * N * N);
	B= (double*) malloc(sizeof(double) * N * N);
	C= (double*) malloc(sizeof(double) * N * N);

	// Value initialization
  init(A, B, C, N);

  double t0 = 0., t1 = 0., duration = 0.;

	// Compute multiplication
  t0 = get_elapsedtime();
  dgemm(N, N, N, 1., A, B, 1., C);
  t1 = get_elapsedtime();

  // Pretty print
  duration = (t1 - t0);
  fprintf(stdout, "CPU Performance results: \n");
  fprintf(stdout, "  %.2f ms\n", duration*1e3);

  free(A);
  free(B);
  free(C);

	return 0;
}

