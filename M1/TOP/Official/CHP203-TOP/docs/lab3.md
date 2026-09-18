# Lab 3: Shared-memory parallelism

An overview of common problems and optimization techniques for shared-memory parallelism.

## False sharing

In this exercise, you'll investigate the performance impact of false sharing in a [multi-threaded C++ code snippet](https://github.com/dssgabriel/TOP-26/lab3/false-sharing) and implement solutions to mitigate this problem.

### Analyzing the problem

1. Explain what is _false sharing_ and why it might be occuring in this code.

2. On a typical x86-64 architecture, what is the typical cache line size?
   How does this relate to the `counters` array layout?

3. Compile and run the provided code with optimization flags.

4. Try running with a different numbers of threads.
   How does performance scale?
   Does it scale linearly with the number of threads as you can expect?

5. Use a profiling tool to measure cache-related metrics.
   What patterns do you observe?

### Fixing the issue

6. Implement at least two different solutions to eliminate false sharing.

7. For each solution, measure and report the performance improvements.

8. Look into [`std::hardware_destructive_interference_size`](https://en.cppreference.com/w/cpp/thread/hardware_destructive_interference_size) as a third solution.
   Measure and report its gains.


## Parallel scan

In this exercise, you'll explore different approaches to implementing parallel prefix sums (scans) and analyze their performance and scalability characteristics.

While reduction operations combine all elements of a sequence into a single value, scan operations compute all the partial reductions.
For example, given an array `[1, 2, 3, 4, 5]`, an _inclusive_ scan produces `[1, 3, 6, 10, 15]` where each element is the sum of all previous elements including itself.
An _exclusive_ scan produces `[0, 1, 3, 6, 10]` where each element is the sum of all previous elements excluding itself.

Scans are fundamental parallel primitives with applications in numerous algorithms including sorting, lexical analysis, and string comparison.

Consider the sample code given in [`integer-scan`](https://github.com/dssgabriel/TOP-26/lab3/integer-scan).

### Sequential implementation

1. Implement the inclusive scan operation sequentially and measure its performance in cycles/element using the `getticks()` function provided in the `"cycle.h"` header.

2. Unlike the reduction operation, what is the theoretical computational complexity of a scan? How does this affect parallel implementation strategies?

3. Compile and run your sequential implementation with both -O0 and -O3 optimization flags. Compare the performance results.

### Parallelization

4. Parallelize the inclusive scan using OpenMP with just `#pragma omp parallel for`. Verify your results against the sequential version.

5. Why does this approach fail to produce correct results? Explain the data dependency pattern in scan operations that makes them more challenging to parallelize than reductions.

### Work-efficient approach

6. Implement the work-efficient parallel scan algorithm, which consists of an up-sweep (reduction) phase and a down-sweep phase.

7. Use OpenMP tasks or sections to parallelize each phase. Note that synchronization between phases is critical.

8. How does the performance compare to the sequential version? What is the theoretical speedup limit for this algorithm?

### Going deeper...

9. In the naive parallelization attempt, one could try to fix the data race using atomic operations.
   Update your implementation to use `#pragma omp atomic`.
   Is this approach viable for scan operations?
   Compare its performance with the other implementations.
   Why are atomic operations generally less effective for scan operations than for reductions?

10. Implement a hybrid approach that combines the work-efficient and blocked methods for larger arrays. What are the trade-offs in choosing block sizes? How does this affect performance across different architectures?

11. Implement a blocked parallel scan where:
  1. The array is divided into blocks;
  2. Each block computes its local scan in parallel;
  3. The last elements of each block are scanned;
  4. The results are propagated back to update each block.

12. What are the limitations of your implementations if you plan to deploy them on many-core architectures like GPUs?
    How would you need to adapt your algorithms for GPU implementation using frameworks like CUDA or OpenCL?
    Propose a GPU-friendly parallel scan algorithm that addresses these limitations.


## NUMA-awareness in parallel redution

Modern multi-socket servers are **Non-Uniform Memory Access (NUMA)** machines.
Each CPU socket has its own local memory bank; accessing *remote* memory (another socket's bank) travels over an interconnect (e.g., AMD Infinity Fabric, Intel UPI) and incurs **2–4x higher latency** and **lower bandwidth** than local access.

Linux follows a **first-touch policy**: a physical page is allocated on the NUMA node of whichever thread *first writes* to it, regardless of who allocated the virtual address.

```
Socket 0                    Socket 1
┌──────────────────┐        ┌──────────────────┐
│  Core 0 … Core N │        │  Core 0 … Core N │
│  L3 Cache        │        │  L3 Cache        │
│  Local DRAM ─────┼──UPI───┼─ Local DRAM      │
└──────────────────┘        └──────────────────┘
```

You are given a skeleton program (`numa_exercise.cpp`) that allocates a large array and performs a **parallel sum reduction** using `std::thread`.

The file contains **two implementations**:

| Function | Description |
|---|---|
| `sum_numa_unaware` | Main thread allocates & initialises the entire array, then spawns workers. |
| `sum_numa_aware`   | Each worker thread initialises its own partition before summing it. |

### Predict (written, no coding required)

1. Which implementation do you expect to be faster on a two-socket machine, and why?

2. Explain what "first-touch" means and how it determines where a page is placed.

3. If this code ran on a **single-socket** machine with uniform memory, would you still expect a performance difference? Justify your answer.

### Measure

1. Compile and run the program on a multi-socket machine (or a NUMA-emulated VM):
   ```bash
   g++ -O2 -std=c++17 -o numa_exercise numa_exercise.cpp -lpthread
   ./numa_exercise
   ```

2. Record the wall-clock times printed for both implementations.

3. Use `numactl --hardware` to confirm the number of NUMA nodes available.

4. Run the unaware version with all threads pinned to a single socket and compare:
   ```bash
   numactl --cpunodebind=0 --membind=0 ./numa_exercise
   ```

### Fix & Extend

1. The `sum_numa_aware` function already demonstrates the fix.
   Explain *precisely* which line change enforces locality and why it works.

2. Modify `sum_numa_unaware` to use `numa_alloc_local()` (from `<numa.h>`) instead of `new`, so each NUMA node allocates its own buffer.
   Measure again.

3. *(Bonus)* Use `pthread_setaffinity_np` to pin each thread to a specific core before it touches memory.
   Does explicit affinity improve consistency of results?

### Expected Observations

On a typical dual-socket machine you should observe the **unaware version running
20–60% slower** than the aware version at large array sizes (≥ 512 MB), because
roughly half the worker threads are performing remote memory accesses for their
entire working set.

