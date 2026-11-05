#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

#include <cuda.h>
#include <cuda_runtime.h>
#define BLOCKSIZE 32
#define CEIL_DIV(a, b) (((a) + (b) - 1) / (b))

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

void mult(double* A, double* B, double* C, int size)
{
  int i = 0, j = 0, k = 0;

	for(i = 0; i < size; i++)
  {
		for(j = 0; j < size; j++)
    {
      double sum = 0.;
			for(k = 0; k < size; k++)
      {
			  sum += A[i * size + k] * B[k * size + j];
			}
      C[i * size + j] = sum;
		}
	}
}

// QUESTION 4
__global__
void dgemm_shared(int M, int N, int K, double alpha, const double *A, const double *B, double beta, double *C)
{
  // the output block that we want to compute in this threadblock
  const uint cRow = blockIdx.x;
  const uint cCol = blockIdx.y;

  // allocate buffer for current block in fast shared mem
  // shared mem is shared between all threads in a block
  __shared__ double As[BLOCKSIZE * BLOCKSIZE];
  __shared__ double Bs[BLOCKSIZE * BLOCKSIZE];

  // the inner row & col that we're accessing in this thread
  const uint threadRow = threadIdx.x / BLOCKSIZE;
  const uint threadCol = threadIdx.x % BLOCKSIZE;

  // advance pointers to the starting positions
  A += cRow * BLOCKSIZE * K;                    // row=cRow, col=0
  B += cCol * BLOCKSIZE;                        // row=0, col=cCol
  C += cRow * BLOCKSIZE * N + cCol * BLOCKSIZE; // row=cRow, col=cCol

  double tmp = 0.0;
  for (int bkIdx = 0; bkIdx < K; bkIdx += BLOCKSIZE) {
    // Have each thread load one of the elements in A & B
    // Make the threadCol (=threadIdx.x) the consecutive index
    // to allow global memory access coalescing
    As[threadRow * BLOCKSIZE + threadCol] = A[threadRow * K + threadCol];
    Bs[threadRow * BLOCKSIZE + threadCol] = B[threadRow * N + threadCol];

    // block threads in this block until cache is fully populated
    __syncthreads();
    A += BLOCKSIZE;
    B += BLOCKSIZE * N;

    // execute the dotproduct on the currently cached block
    for (int dotIdx = 0; dotIdx < BLOCKSIZE; ++dotIdx) {
      tmp += As[threadRow * BLOCKSIZE + dotIdx] *
             Bs[dotIdx * BLOCKSIZE + threadCol];
    }
    // need to sync again at the end, to avoid faster threads
    // fetching the next block into the cache before slower threads are done
    __syncthreads();
  }
  C[threadRow * N + threadCol] =
      alpha * tmp + beta * C[threadRow * N + threadCol];
}
// FIN QUESTION 4

int main(int argc, char** argv){
	int N;

	double *A;
	double *B;
	double *C;

	N = (argc < 2)?1000:atoi(argv[1]);
	fprintf(stdout, "Matrix Multiplication\n  Size: %dx%d\n", N, N);

	// Memory allocation
	A= (double*) malloc(sizeof(double) * N * N);
	B= (double*) malloc(sizeof(double) * N * N);
	C= (double*) malloc(sizeof(double) * N * N);

	// Value initialization
  init(A, B, C, N);

  // QUESTION 1
	double *d_A, *d_B, *d_C;
	cudaMalloc(&d_A, sizeof(double) * N * N);
	cudaMalloc(&d_B, sizeof(double) * N * N);
	cudaMalloc(&d_C, sizeof(double) * N * N);
  // FIN QUESTION 1

  // QUESTION 2
	cudaMemcpy(d_A, A, sizeof(double) * N * N, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, B, sizeof(double) * N * N, cudaMemcpyHostToDevice);
	cudaMemcpy(d_C, C, sizeof(double) * N * N, cudaMemcpyHostToDevice);
  // FIN QUESTION 2

  // QUESTION 3
  dim3 gridDim(CEIL_DIV(N, BLOCKSIZE), CEIL_DIV(N, BLOCKSIZE));
  dim3 blockDim(BLOCKSIZE * BLOCKSIZE);
  // FIN QUESTION 3

  cudaStream_t stream;
  cudaStreamCreate(&stream);

  cudaEvent_t start;
  cudaEvent_t stop;

  // create the events
  cudaEventCreate(&start);
  cudaEventCreate(&stop);

  // record the start event
  cudaEventRecord(start, stream);

  // QUESTION 4
    cudaFuncSetAttribute(dgemm_shared,
                       cudaFuncAttributePreferredSharedMemoryCarveout,
                       cudaSharedmemCarveoutMaxShared);
	dgemm_shared<<<gridDim, blockDim, 2*32*32*sizeof(double), stream>>>(N, N, N, 1., d_A, d_B, 1., d_C);
  // FIN QUESTION 4

  // record the stop event
  cudaEventRecord(stop, stream);

  // wait for the stream to complete
  // both events will have been triggered
  cudaStreamSynchronize(stream);

  // get the timing
  float elapsedTime;
  cudaEventElapsedTime(&elapsedTime, start, stop);

  // clean up
  cudaEventDestroy(start);
  cudaEventDestroy(stop);
  cudaStreamDestroy(stream);

  uint64_t nb_op = (2ULL * N*N*N) + (3ULL * N * N);
  fprintf(stdout, "Performance results: \n");
  fprintf(stdout, "  %lf ms\n", elapsedTime);
  //fprintf(stdout, "  Nb Op: %lf\n", (double)nb_op);
  double flops = (double)nb_op / (elapsedTime * 1e6);
  fprintf(stdout, "  %.2f GFlops\n", flops);

  // QUESTION 5
	cudaMemcpy(C, d_C, sizeof(double) * N * N, cudaMemcpyDeviceToHost);
  // FIN QUESTION 5
#ifdef DBG
  for(int i = 0; i < 5; ++i)
    for(int j = 0; j < 5; ++j)
    {
      fprintf(stdout, "C[%d][%d] = %g\n", i, j, C[i * N + j]);
      C[i * N + j] = 0.;
    }

  double t0 = 0., t1 = 0., duration = 0.;

	// Compute multiplication
  t0 = get_elapsedtime();
  mult(A, B, C, N);
  t1 = get_elapsedtime();

  fprintf(stdout, "\n");
  for(int i = 0; i < 5; ++i)
    for(int j = 0; j < 5; ++j)
    {
      fprintf(stdout, "C[%d][%d] = %g\n", i, j, C[i * N + j]);
      C[i * N + j] = 0.;
    }

  // Pretty print
  duration = (t1 - t0);
  fprintf(stdout, "Performance results: \n");
	fprintf(stdout, "  Time: %lf s\n", duration);
  fprintf(stdout, "  GFlops: %.2f\n", (nb_op / duration)*1E-9);
#endif

  free(A);
  free(B);
  free(C);

  cudaFree(A);
  cudaFree(B);
  cudaFree(C);

	return 0;
}

