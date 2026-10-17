#include <cstdio>
#include <cstdlib>
#include <cuda_runtime.h>

constexpr int error_exit_code = -1;

/// \brief Checks if the provided error code is \p cudaSuccess and if not,
/// prints an error message to the standard error output and terminates the program
/// with an error code.
#define CUDA_CHECK(condition)                                                \
    do {                                                                     \
        const cudaError_t error = (condition);                               \
        if (error != cudaSuccess) {                                          \
            fprintf(stderr, "An error encountered: \" %s \" at %s:%d\n",     \
                    cudaGetErrorString(error), __FILE__, __LINE__);          \
            exit(error_exit_code);                                           \
        }                                                                    \
    } while (0)

__global__ void kernel(int *v)
{
  *v = 1;
}

int main(int argc, char **argv)
{
  int sz_in_bytes = sizeof(int);

  int *h_a;
  int *d_a;

  int nDevices;

  CUDA_CHECK(cudaSetDevice(0));

  // Querying the CUDA device properties
  cudaGetDeviceCount(&nDevices);
  for (int i = 0; i < nDevices; i++) {
    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, i);
    printf("Device Number: %d\n", i);
    printf("  Device name: %s\n", prop.name);
    printf("  Memory Clock Rate (KHz): %d\n",
           prop.memoryClockRate);
    printf("  Memory Bus Width (bits): %d\n",
           prop.memoryBusWidth);
    printf("  Peak Memory Bandwidth (GB/s): %f\n",
           2.0*prop.memoryClockRate*(prop.memoryBusWidth/8)/1.0e6);
    printf("  Device Compute Capability: %d.%d\n",
           prop.major, prop.minor);
    printf("  > Kernel Configuration information\n");
    printf("    - Warp Size: %d\n",
           prop.warpSize);
    printf("    - Max Threads Per Block: %d\n",
           prop.maxThreadsPerBlock);
    printf("    - Max size of each dimension of a Block: (%d, %d, %d)\n",
           prop.maxThreadsDim[0], prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
    printf("    - Max size of each dimension of a Grid: (%d, %d, %d)\n",
           prop.maxGridSize[0], prop.maxGridSize[1], prop.maxGridSize[2]);
    printf("  > Memory information\n");
    printf("    - Total Global Memory size (bytes): %zu\n",
           prop.totalGlobalMem);
    printf("    - Max Shared Memory size per block (bytes): %zu\n",
           prop.sharedMemPerBlock);
    printf("    - Max Constant Memory size (bytes): %zu\n\n",
           prop.totalConstMem);
  }

  // Allocation on host (malloc)
  h_a = (int*)malloc(sz_in_bytes);
  *h_a = 0;

  // Allocation on device (cudaMalloc)
  cudaMalloc((void**)&d_a, sz_in_bytes);

  // Copying data to device (cudaMemcpy)
  cudaMemcpy(d_a, h_a, sz_in_bytes, cudaMemcpyHostToDevice);

  // Kernel configuration
  dim3  dimBlock(1, 1, 1);
  dim3  dimGrid(1, 1, 1);

  // Kernel launch
  kernel<<<dimGrid , dimBlock>>>(d_a);

  // Retrieving data from device (cudaMemcpy)
  cudaMemcpy(h_a, d_a, sz_in_bytes, cudaMemcpyDeviceToHost);

  // Freeing on device (cudaFree)
  cudaFree(d_a);

  // Verifying if  
  if(*h_a == 1)
  {
    fprintf(stderr, "TEST PASSED !\n");
  }
  else
  {
    fprintf(stderr, "TEST FAILED !\n");
  }

  free(h_a);

  return 0;
}
