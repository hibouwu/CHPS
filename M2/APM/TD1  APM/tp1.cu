#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void kernel(double *x, double *y, double alpha, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < N)
    {
    	y[i] = alpha * x[i] + y[i];
    }
}

int main(int argc, char **argv)
{
    int N = 1000;
    int sz_in_bytes = N*sizeof(double);

    double *h_x, *h_y;
    double *d_x, *d_y;

    h_x = (double*)malloc(sz_in_bytes);
    h_y = (double*)malloc(sz_in_bytes);

    double alpha = 3.14;

    // Initiate values on h_a and h_b
    for(int i = 0 ; i < N ; i++)
    {
	    h_x[i] = 1./(1.+i);
	    h_y[i] = (i-1.)/(i+1.);
    }

    // 3-arrays allocation on device 
    cudaMalloc((void**)&d_x, sz_in_bytes);
    cudaMalloc((void**)&d_y, sz_in_bytes);

    // copy on device values pointed on host by h_a and h_b
    // (the new values are pointed by d_a et d_b on device)
    cudaMemcpy(d_x, h_x, sz_in_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, h_y, sz_in_bytes, cudaMemcpyHostToDevice);

    dim3  dimBlock(64, 1, 1);
    dim3  dimGrid((N + dimBlock.x - 1)/dimBlock.x, 1, 1);
    kernel<<<dimGrid , dimBlock>>>(d_x, d_y, alpha, N);

    // Result is pointed by d_c on device
    // Copy this result on host (result pointed by h_c on host)
    cudaMemcpy(h_y, d_y, sz_in_bytes, cudaMemcpyDeviceToHost);

    // freeing on device 
    cudaFree(d_x);
    cudaFree(d_y);

    free(h_x);
    free(h_y);

    return 0;
}
