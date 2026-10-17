#include <cuda_runtime.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>

#define CUDA_CHECK(call) do { \
    cudaError_t error = (call); \
    if (error != cudaSuccess) { \
        fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, cudaGetErrorString(error)); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

double get_elapsedtime() {
    timespec now;
    if (clock_gettime(CLOCK_MONOTONIC_RAW, &now) != 0) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    return now.tv_sec + 1e-9 * now.tv_nsec;
}

// Same initialization and loop order as the supplied dgemm.c.
void init(double *A, double *B, double *C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = i * 1.0;
            B[i * N + j] = i * 1.0;
            C[i * N + j] = 0.0;
        }
    }
}

void dgemm(int M, int N, int K, double alpha, const double *A,
           const double *B, double beta, double *C) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < K; k++) {
                sum += A[i * K + k] * B[k * N + j];
            }
            C[i * N + j] = alpha * sum + beta * C[i * N + j];
        }
    }
}

__global__ void dgemm_kernel(int N, double alpha, const double *A,
                             const double *B, double beta, double *C) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row >= N || col >= N) return;
    double sum = 0.0;
    for (int k = 0; k < N; k++) {
        sum += A[row * N + k] * B[k * N + col];
    }
    C[row * N + col] = alpha * sum + beta * C[row * N + col];
}

double median(std::vector<double> values) {
    std::sort(values.begin(), values.end());
    size_t middle = values.size() / 2;
    if (values.size() % 2 != 0) return values[middle];
    return (values[middle - 1] + values[middle]) / 2.0;
}

int main(int argc, char **argv) {
    int N = argc > 1 ? atoi(argv[1]) : 1024;
    int repetitions = argc > 2 ? atoi(argv[2]) : 5;
    bool general_input = argc > 3 && strcmp(argv[3], "general") == 0;
    if (N < 1 || N > 4096 || repetitions < 1 || repetitions > 100) {
        fprintf(stderr, "Usage: %s [N:1..4096] [repetitions:1..100] [general]\n", argv[0]);
        return EXIT_FAILURE;
    }
    CUDA_CHECK(cudaSetDevice(0));
    cudaDeviceProp prop;
    CUDA_CHECK(cudaGetDeviceProperties(&prop, 0));
    if (prop.maxThreadsPerBlock < 1024 || prop.maxThreadsDim[0] < 32 ||
        prop.maxThreadsDim[1] < 32) {
        fprintf(stderr, "The GPU cannot run the required 32x32 block.\n");
        return EXIT_FAILURE;
    }
    printf("DEVICE name=%s cc=%d.%d block=32x32\n", prop.name, prop.major, prop.minor);
    size_t count = (size_t)N * N;
    size_t bytes = count * sizeof(double);
    std::vector<double> A(count), B(count), C_initial(count), C_cpu(count), C_gpu(count);
    init(A.data(), B.data(), C_initial.data(), N);
    double alpha = 1.0, beta = 1.0;
    if (general_input) {
        alpha = 0.75;
        beta = -0.5;
        for (size_t i = 0; i < count; i++) {
            A[i] = ((int)(i % 19) - 9) / 11.0;
            B[i] = ((int)((i * 7 + 3) % 23) - 11) / 13.0;
            C_initial[i] = ((int)(i % 17) - 8) / 7.0;
        }
    }
    double *d_A, *d_B, *d_C;
    CUDA_CHECK(cudaMalloc((void **)&d_A, bytes));
    CUDA_CHECK(cudaMalloc((void **)&d_B, bytes));
    CUDA_CHECK(cudaMalloc((void **)&d_C, bytes));
    CUDA_CHECK(cudaMemcpy(d_A, A.data(), bytes, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_B, B.data(), bytes, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_C, C_initial.data(), bytes, cudaMemcpyHostToDevice));
    dim3 block(32, 32);
    dim3 grid((N + 31) / 32, (N + 31) / 32);

    // Warm up both implementations once. Restore C outside every timed region.
    C_cpu = C_initial;
    dgemm(N, N, N, alpha, A.data(), B.data(), beta, C_cpu.data());
    dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());

    cudaEvent_t start, stop;
    CUDA_CHECK(cudaEventCreate(&start));
    CUDA_CHECK(cudaEventCreate(&stop));
    std::vector<double> cpu_times, kernel_times, gpu_with_copy_times;
    double max_cpu_error = 0.0, max_gpu_error = 0.0;
    size_t failures = 0;
    for (int repeat = 0; repeat < repetitions; repeat++) {
        C_cpu = C_initial;
        double cpu_start = get_elapsedtime();
        dgemm(N, N, N, alpha, A.data(), B.data(), beta, C_cpu.data());
        double cpu_ms = (get_elapsedtime() - cpu_start) * 1e3;

        CUDA_CHECK(cudaMemcpy(d_C, C_initial.data(), bytes, cudaMemcpyHostToDevice));
        CUDA_CHECK(cudaDeviceSynchronize());
        double gpu_start = get_elapsedtime();
        CUDA_CHECK(cudaEventRecord(start));
        dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
        CUDA_CHECK(cudaGetLastError());
        CUDA_CHECK(cudaEventRecord(stop));
        CUDA_CHECK(cudaMemcpy(C_gpu.data(), d_C, bytes, cudaMemcpyDeviceToHost));
        double gpu_with_copy_ms = (get_elapsedtime() - gpu_start) * 1e3;
        CUDA_CHECK(cudaEventSynchronize(stop));
        float kernel_ms;
        CUDA_CHECK(cudaEventElapsedTime(&kernel_ms, start, stop));
        cpu_times.push_back(cpu_ms);
        kernel_times.push_back(kernel_ms);
        gpu_with_copy_times.push_back(gpu_with_copy_ms);
        printf("SAMPLE repeat=%d cpu_ms=%.9f kernel_ms=%.9f gpu_with_copy_ms=%.9f\n",
               repeat, cpu_ms, kernel_ms, gpu_with_copy_ms);

        // Independent reference: closed form for the supplied input;
        // long-double scalar accumulation for the additional small cases.
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                size_t index = (size_t)row * N + col;
                long double reference = (long double)row * N * (N - 1) / 2;
                if (general_input) {
                    long double sum = 0.0L;
                    for (int k = 0; k < N; k++) {
                        sum += (long double)A[row * N + k] * B[k * N + col];
                    }
                    reference = (long double)alpha * sum + (long double)beta * C_initial[index];
                }
                double cpu_error = (double)std::abs((long double)C_cpu[index] - reference);
                double gpu_error = (double)std::abs((long double)C_gpu[index] - reference);
                max_cpu_error = std::max(max_cpu_error, cpu_error);
                max_gpu_error = std::max(max_gpu_error, gpu_error);
                double tolerance = 1e-10 + 1e-10 * (double)std::abs(reference);
                if (!std::isfinite(C_cpu[index]) || !std::isfinite(C_gpu[index]) ||
                    cpu_error > tolerance || gpu_error > tolerance) failures++;
            }
        }
    }
    double cpu_ms = median(cpu_times);
    double kernel_ms = median(kernel_times);
    double total_ms = median(gpu_with_copy_times);
    double flops = 2.0 * N * N * N;
    printf("RESULT N=%d repetitions=%d input=%s alpha=%.2f beta=%.2f "
           "cpu_ms=%.9f kernel_ms=%.9f gpu_with_copy_ms=%.9f "
           "cpu_gflops=%.6f kernel_gflops=%.6f effective_gflops=%.6f "
           "kernel_speedup=%.6f with_copy_speedup=%.6f "
           "max_cpu_error=%.12g max_gpu_error=%.12g failures=%zu validation=%s\n",
           N, repetitions, general_input ? "general" : "course", alpha, beta,
           cpu_ms, kernel_ms, total_ms, flops / (cpu_ms * 1e6),
           flops / (kernel_ms * 1e6), flops / (total_ms * 1e6),
           cpu_ms / kernel_ms, cpu_ms / total_ms, max_cpu_error, max_gpu_error,
           failures, failures == 0 ? "PASSED" : "FAILED");
    CUDA_CHECK(cudaEventDestroy(start));
    CUDA_CHECK(cudaEventDestroy(stop));
    CUDA_CHECK(cudaFree(d_A));
    CUDA_CHECK(cudaFree(d_B));
    CUDA_CHECK(cudaFree(d_C));
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
