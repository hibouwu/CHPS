// TP3 Q1-Q17. The teacher's source is included unchanged for its exact kernel.
// Its main is renamed and never called; the safe driver below owns execution.
#define main supplied_main_do_not_call
#include "teacher_2d.cu"
#undef main

#include <algorithm>
#include <cerrno>
#include <climits>
#include <cmath>
#include <cstring>
#include <vector>

#define CUDA_CHECK(call) do { \
    cudaError_t status_ = (call); \
    if (status_ != cudaSuccess) { \
        fprintf(stderr, "%s:%d: %s: %s\n", __FILE__, __LINE__, #call, \
                cudaGetErrorString(status_)); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

// Same 32x32 output tile as the supplied kernel, with zero-filled edge tiles.
// TM=1: one output/thread, 1024 threads. TM=4: four outputs/thread, 256 threads.
template<int TM>
__global__ void dgemm_safe(int M, int N, int K, double alpha,
                          const double* A, const double* B, double beta, double* C) {
    constexpr int BS = 32;
    constexpr int THREADS = BS * BS / TM;
    __shared__ double As[BS * BS];
    __shared__ double Bs[BS * BS];
    const int tx = threadIdx.x;
    const int col = tx % BS;
    const int row0 = (tx / BS) * TM;
    const int base_row = blockIdx.x * BS;  // keep the teacher's x=row convention
    const int base_col = blockIdx.y * BS;
    double acc[TM] = {};
    for (int k0 = 0; k0 < K; k0 += BS) {
        for (int p = tx; p < BS * BS; p += THREADS) {
            const int r = p / BS, c = p % BS;
            As[p] = (base_row + r < M && k0 + c < K)
                  ? A[(size_t)(base_row + r) * K + k0 + c] : 0.0;
            Bs[p] = (k0 + r < K && base_col + c < N)
                  ? B[(size_t)(k0 + r) * N + base_col + c] : 0.0;
        }
        __syncthreads();
        #pragma unroll
        for (int k = 0; k < BS; ++k) {
            const double b = Bs[k * BS + col];
            #pragma unroll
            for (int t = 0; t < TM; ++t)
                acc[t] = fma(As[(row0 + t) * BS + k], b, acc[t]);
        }
        __syncthreads(); // all threads participate, including edge threads
    }
    #pragma unroll
    for (int t = 0; t < TM; ++t) {
        const int r = base_row + row0 + t, c = base_col + col;
        if (r < M && c < N) {
            const size_t p = (size_t)r * N + c;
            C[p] = alpha * acc[t] + beta * C[p];
        }
    }
}

static size_t round_up(size_t x, size_t unit) {
    return (x + unit - 1) / unit * unit;
}

static void report(const char* name, const void* kernel, int threads, size_t dynamic,
                   const cudaDeviceProp& p) {
    CUDA_CHECK(cudaFuncSetAttribute(kernel, cudaFuncAttributePreferredSharedMemoryCarveout,
                                    cudaSharedmemCarveoutMaxShared));
    cudaFuncAttributes a{};
    CUDA_CHECK(cudaFuncGetAttributes(&a, kernel));
    const int warps = (threads + p.warpSize - 1) / p.warpSize;
    // The worksheet's pedagogical register-allocation model, NOT a universal rule.
    const size_t regs_warp = round_up((size_t)a.numRegs * p.warpSize, 256);
    const size_t regs_block = regs_warp * warps;
    const size_t smem = a.sharedSizeBytes + dynamic;
    const int bs = smem ? p.sharedMemPerMultiprocessor / smem : INT_MAX;
    const int bt = p.maxThreadsPerMultiProcessor / threads;
    const int br = regs_block ? p.regsPerMultiprocessor / regs_block : INT_MAX;
    const int bw = (p.maxThreadsPerMultiProcessor / p.warpSize) / warps;
    int manual = std::min(std::min(bs, bt), std::min(br, p.maxBlocksPerMultiProcessor));
    manual = std::min(manual, bw);
    // Also check single-block launch limits before presenting any capacity.
    if (threads > a.maxThreadsPerBlock || threads > p.maxThreadsPerBlock ||
        smem > p.sharedMemPerBlock || regs_block > (size_t)p.regsPerBlock)
        manual = 0;
    int api = 0;
    CUDA_CHECK(cudaOccupancyMaxActiveBlocksPerMultiprocessor(&api, kernel, threads, dynamic));
    const int maxwarps = p.maxThreadsPerMultiProcessor / p.warpSize;
    printf("\nKERNEL %s\n", name);
    printf("threads=%d warps_per_block=%d registers_per_thread=%d registers_per_warp_raw=%d\n",
           threads, warps, a.numRegs, a.numRegs * p.warpSize);
    printf("registers_per_warp_rounded=%zu registers_per_block_model=%zu local_bytes_per_thread=%zu\n",
           regs_warp, regs_block, a.localSizeBytes);
    printf("static_smem=%zu dynamic_smem=%zu total_user_smem=%zu\n",
           a.sharedSizeBytes, dynamic, smem);
    printf("blocks_smem_model=%d blocks_threads=%d blocks_registers_model=%d blocks_warps=%d blocks_hardware=%d\n",
           bs, bt, br, bw, p.maxBlocksPerMultiProcessor);
    printf("manual_blocks=%d manual_warps=%d manual_occupancy_pct=%.6f api_blocks=%d api_warps=%d api_occupancy_pct=%.6f\n",
           manual, manual * warps, 100.0 * manual * warps / maxwarps,
           api, api * warps, 100.0 * api * warps / maxwarps);
    if (manual != api)
        printf("NOTE pedagogical model differs from runtime; use API for allocation/subpartition constraints.\n");
}

static int positive_int(const char* arg) {
    char* end = nullptr;
    errno = 0;
    const long v = strtol(arg, &end, 10);
    // Bound dimensions to keep integer tile arithmetic safe; allocation is checked too.
    if (errno || *end || v <= 0 || v > 32768) {
        fprintf(stderr, "Expected integer in [1,32768], got '%s'\n", arg);
        exit(EXIT_FAILURE);
    }
    return (int)v;
}

static void launch(const void* kernel, int threads, size_t dynamic, int M, int N, int K,
                   double alpha, double* A, double* B, double beta, double* C) {
    void* args[] = {&M, &N, &K, &alpha, &A, &B, &beta, &C};
    CUDA_CHECK(cudaLaunchKernel(kernel, dim3((M + 31) / 32, (N + 31) / 32),
                               (kernel == (const void*)dgemm_shared ? dim3(32, 32) : dim3(threads)), args, dynamic, nullptr));
    CUDA_CHECK(cudaGetLastError());
}

static bool check_cpu(const std::vector<double>& A, const std::vector<double>& B,
                      const std::vector<double>& C0, const std::vector<double>& got,
                      int M, int N, int K, double alpha, double beta) {
    const size_t count = (size_t)M * N;
    const bool full = count * K <= 32000000ULL;
    const size_t samples = full ? count : std::min(count, (size_t)128);
    double max_abs = 0, max_scaled = 0;
    for (size_t s = 0; s < samples; ++s) {
        // Include corners, then a reproducible spread through the output.
        const size_t p = full ? s : s == 0 ? 0 : s == 1 ? count - 1
                                     : (s * 104729ULL + 17) % count;
        const size_t r = p / N, c = p % N;
        long double sum = 0;
        for (int k = 0; k < K; ++k)
            sum += (long double)A[r * K + k] * B[(size_t)k * N + c];
        const double ref = (double)(alpha * sum + beta * (long double)C0[p]);
        const double err = fabs(got[p] - ref);
        if (!std::isfinite(got[p]) || err > 1e-10 * (1 + fabs(ref))) {
            fprintf(stderr, "CPU FAIL p=%zu got=%.17g ref=%.17g\n", p, got[p], ref);
            return false;
        }
        max_abs = std::max(max_abs, err);
        max_scaled = std::max(max_scaled, err / (1 + fabs(ref)));
    }
    printf("CPU_CHECK mode=%s checked=%zu/%zu max_abs=%.9g max_scaled=%.9g PASS\n",
           full ? "full" : "sampled", samples, count, max_abs, max_scaled);
    return true;
}

static std::vector<double> run(const char* name, const void* kernel, int threads,
                              size_t dynamic, int M, int N, int K, int repeats,
                              double alpha, double* dA, double* dB, double beta,
                              double* dC, double* dC0, const std::vector<double>& A,
                              const std::vector<double>& B, const std::vector<double>& C0) {
    const size_t bytes = C0.size() * sizeof(double);
    CUDA_CHECK(cudaMemcpy(dC, dC0, bytes, cudaMemcpyDeviceToDevice));
    launch(kernel, threads, dynamic, M, N, K, alpha, dA, dB, beta, dC);
    CUDA_CHECK(cudaDeviceSynchronize());
    std::vector<double> result(C0.size());
    CUDA_CHECK(cudaMemcpy(result.data(), dC, bytes, cudaMemcpyDeviceToHost));
    printf("\nRESULT %s M=%d N=%d K=%d alpha=%.2f beta=%.2f\n", name, M, N, K, alpha, beta);
    if (!check_cpu(A, B, C0, result, M, N, K, alpha, beta)) exit(EXIT_FAILURE);
    cudaEvent_t start, stop;
    CUDA_CHECK(cudaEventCreate(&start));
    CUDA_CHECK(cudaEventCreate(&stop));
    std::vector<float> timings;
    for (int i = -2; i < repeats; ++i) {
        // Reset outside event interval: every run has identical nonzero C input.
        CUDA_CHECK(cudaMemcpyAsync(dC, dC0, bytes, cudaMemcpyDeviceToDevice));
        CUDA_CHECK(cudaEventRecord(start));
        launch(kernel, threads, dynamic, M, N, K, alpha, dA, dB, beta, dC);
        CUDA_CHECK(cudaEventRecord(stop));
        CUDA_CHECK(cudaEventSynchronize(stop));
        float ms = 0;
        CUDA_CHECK(cudaEventElapsedTime(&ms, start, stop));
        if (i >= 0) timings.push_back(ms);
    }
    printf("SAMPLES_MS %s", name);
    for (float ms : timings) printf(" %.9g", ms);
    printf("\n");
    std::sort(timings.begin(), timings.end());
    const double median = (timings[(repeats - 1) / 2] + timings[repeats / 2]) / 2.0;
    printf("TIMING %s repeats=%d median_ms=%.9g min_ms=%.9g max_ms=%.9g gemm_gflops=%.9g\n",
           name, repeats, median, timings.front(), timings.back(),
           2.0 * M * N * K / (median * 1e6));
    CUDA_CHECK(cudaEventDestroy(start));
    CUDA_CHECK(cudaEventDestroy(stop));
    return result;
}

int main(int argc, char** argv) {
    printf("TEACHER_LAYOUT x=32 y=32 z=1 total_threads=1024\n");
    if (argc != 1 && argc != 2 && argc != 4 && argc != 5) {
        fprintf(stderr, "Usage: %s [size] or %s M N K [repeats]\n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }
    const int M = argc >= 2 ? positive_int(argv[1]) : 256;
    const int N = argc >= 4 ? positive_int(argv[2]) : M;
    const int K = argc >= 4 ? positive_int(argv[3]) : M;
    const int repeats = argc == 5 ? positive_int(argv[4]) : 7;
    int device = 0, runtime = 0, driver = 0;
    CUDA_CHECK(cudaGetDevice(&device));
    cudaDeviceProp p{};
    CUDA_CHECK(cudaGetDeviceProperties(&p, device));
    CUDA_CHECK(cudaRuntimeGetVersion(&runtime));
    CUDA_CHECK(cudaDriverGetVersion(&driver));
    printf("DEVICE name=%s cc=%d.%d SMs=%d runtime=%d driver=%d\n", p.name, p.major,
           p.minor, p.multiProcessorCount, runtime, driver);
    printf("SM shared=%zu threads=%d registers=%d max_blocks=%d warp_size=%d\n",
           p.sharedMemPerMultiprocessor, p.maxThreadsPerMultiProcessor,
           p.regsPerMultiprocessor, p.maxBlocksPerMultiProcessor, p.warpSize);
    printf("BLOCK shared_default=%zu shared_optin=%zu threads=%d registers=%d reserved_smem=%zu\n",
           p.sharedMemPerBlock, p.sharedMemPerBlockOptin, p.maxThreadsPerBlock,
           p.regsPerBlock, p.reservedSharedMemPerBlock);
    report("original_extra_smem", (const void*)dgemm_shared, 1024, 16384, p);
    report("original_no_extra_smem", (const void*)dgemm_shared, 1024, 0, p);
    report("shared_safe", (const void*)dgemm_safe<1>, 1024, 0, p);
    report("tiled_tm4", (const void*)dgemm_safe<4>, 256, 0, p);
    std::vector<double> A((size_t)M * K), B((size_t)K * N), C0((size_t)M * N);
    // Signed, varying data and nonzero C exercise indexing and alpha/beta semantics.
    for (size_t i = 0; i < A.size(); ++i) A[i] = ((int)(i % 97) - 48) / 53.0;
    for (size_t i = 0; i < B.size(); ++i) B[i] = ((int)((i * 7) % 89) - 44) / 47.0;
    for (size_t i = 0; i < C0.size(); ++i) C0[i] = ((int)(i % 31) - 15) / 17.0;
    double *dA, *dB, *dC, *dC0;
    CUDA_CHECK(cudaMalloc(&dA, A.size() * sizeof(double)));
    CUDA_CHECK(cudaMalloc(&dB, B.size() * sizeof(double)));
    CUDA_CHECK(cudaMalloc(&dC, C0.size() * sizeof(double)));
    CUDA_CHECK(cudaMalloc(&dC0, C0.size() * sizeof(double)));
    CUDA_CHECK(cudaMemcpy(dA, A.data(), A.size() * sizeof(double), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(dB, B.data(), B.size() * sizeof(double), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(dC0, C0.data(), C0.size() * sizeof(double), cudaMemcpyHostToDevice));
    constexpr double alpha = 1.25, beta = -0.5;
    if (M % 32 == 0 && N % 32 == 0 && K % 32 == 0) {
        run("original_extra_smem", (const void*)dgemm_shared, 1024, 16384,
            M, N, K, repeats, alpha, dA, dB, beta, dC, dC0, A, B, C0);
        run("original_no_extra_smem", (const void*)dgemm_shared, 1024, 0,
            M, N, K, repeats, alpha, dA, dB, beta, dC, dC0, A, B, C0);
    } else {
        printf("\nSKIP original kernels: dimensions must be multiples of 32 (no edge guards).\n");
    }
    const auto baseline = run("shared_safe", (const void*)dgemm_safe<1>, 1024, 0,
                             M, N, K, repeats, alpha, dA, dB, beta, dC, dC0, A, B, C0);
    const auto tiled = run("tiled_tm4", (const void*)dgemm_safe<4>, 256, 0,
                          M, N, K, repeats, alpha, dA, dB, beta, dC, dC0, A, B, C0);
    double max_error = 0;
    for (size_t i = 0; i < baseline.size(); ++i) {
        if (!std::isfinite(baseline[i]) || !std::isfinite(tiled[i]) ||
            fabs(baseline[i] - tiled[i]) > 1e-10 * (1 + fabs(baseline[i]))) {
            fprintf(stderr, "GPU_COMPARE FAIL at %zu\n", i);
            return EXIT_FAILURE;
        }
        max_error = std::max(max_error, fabs(baseline[i] - tiled[i]));
    }
    printf("GPU_COMPARE checked=%zu max_abs=%.9g PASS\n", baseline.size(), max_error);
    CUDA_CHECK(cudaFree(dA)); CUDA_CHECK(cudaFree(dB));
    CUDA_CHECK(cudaFree(dC)); CUDA_CHECK(cudaFree(dC0));
    return EXIT_SUCCESS;
}
