# Lab 4: Shared-memory parallelism 实验4：共享内存并行

An overview of common problems and optimization techniques for shared-memory parallelism. 共享内存并行中常见问题与优化技术概述。

## False sharing 伪共享

In this exercise, you'll investigate the performance impact of false sharing in a [multi-threaded C++ code snippet](https://github.com/dssgabriel/TOP-26/lab4/false-sharing) and implement solutions to mitigate this problem. 在本练习中，你将研究伪共享在一个[多线程 C++ 代码示例](https://github.com/dssgabriel/TOP-26/lab4/false-sharing)中的性能影响，并实现缓解该问题的方案。

### Analyzing the problem 分析问题

1. Explain what is _false sharing_ and why it might be occuring in this code. 1. 解释什么是 _false sharing_（伪共享），以及为什么它可能会在这段代码中发生。

2. On a typical x86-64 architecture, what is the typical cache line size? 2. 在典型的 x86-64 架构上，缓存行的典型大小是多少？
   How does this relate to the `counters` array layout? 这与 `counters` 数组的布局有什么关系？

3. Compile and run the provided code with optimization flags. 3. 使用优化选项编译并运行提供的代码。

4. Try running with a different numbers of threads. 4. 尝试使用不同数量的线程运行。
   How does performance scale? 性能如何扩展？
   Does it scale linearly with the number of threads as you can expect? 它是否像你预期的那样随线程数量线性扩展？

5. Use a profiling tool to measure cache-related metrics. 5. 使用性能分析工具测量与缓存相关的指标。
   What patterns do you observe? 你观察到了哪些模式？

### Fixing the issue 解决该问题

6. Implement at least two different solutions to eliminate false sharing. 6. 至少实现两种不同的方案来消除伪共享。

7. For each solution, measure and report the performance improvements. 7. 对每种方案测量并报告性能提升。

8. Look into [`std::hardware_destructive_interference_size`](https://en.cppreference.com/w/cpp/thread/hardware_destructive_interference_size) as a third solution. 8. 将 [`std::hardware_destructive_interference_size`](https://en.cppreference.com/w/cpp/thread/hardware_destructive_interference_size) 作为第三种方案进行研究。
   Measure and report its gains. 测量并报告它带来的收益。


## NUMA-unaware vs. NUMA-aware parallel redution 非 NUMA 感知与 NUMA 感知的并行归约

Modern multi-socket servers are **Non-Uniform Memory Access (NUMA)** machines. 现代多路服务器属于 **Non-Uniform Memory Access (NUMA)** 机器。
Each CPU socket has its own local memory bank; accessing *remote* memory (another socket's bank) travels over an interconnect (e.g., AMD Infinity Fabric, Intel UPI) and incurs **2–4x higher latency** and **lower bandwidth** than local access. 每个 CPU 插槽都有自己的本地内存；访问*远程*内存（另一个插槽的内存）需要通过互连（例如 AMD Infinity Fabric、Intel UPI），其延迟比本地访问高 **2 到 4 倍**，带宽也更低。

Linux follows a **first-touch policy**: a physical page is allocated on the NUMA node of whichever thread *first writes* to it, regardless of who allocated the virtual address. Linux 采用 **first-touch policy**（首次触碰策略）：物理页会被分配到*首次写入*该页的线程所在的 NUMA 节点上，而不管是谁分配了这个虚拟地址。

``` 
Socket 0                    Socket 1
┌──────────────────┐        ┌──────────────────┐
│  Core 0 … Core N │        │  Core 0 … Core N │
│  L3 Cache        │        │  L3 Cache        │
│  Local DRAM ─────┼──UPI───┼─ Local DRAM      │
└──────────────────┘        └──────────────────┘
```

You are given a skeleton program (`numa_exercise.cpp`) that allocates a large array and performs a **parallel sum reduction** using `std::thread`. 现提供一个骨架程序（`numa_exercise.cpp`），它会分配一个大数组，并使用 `std::thread` 执行**并行求和归约**。

The file contains **two implementations**: 该文件包含**两种实现**：

| Function 函数 | Description 描述 |
|---|---|
| `sum_numa_unaware` | Main thread allocates & initialises the entire array, then spawns workers. 主线程分配并初始化整个数组，然后再创建工作线程。 |
| `sum_numa_aware`   | Each worker thread initialises its own partition before summing it. 每个工作线程在求和前先初始化自己负责的分区。 |

### Predict (written, no coding required) 预测（书面回答，无需编码）

1. Which implementation do you expect to be faster on a two-socket machine, and why? 1. 在双路机器上，你预计哪种实现会更快？为什么？

2. Explain what "first-touch" means and how it determines where a page is placed. 2. 解释 “first-touch” 是什么，以及它如何决定一个页面被放置在哪个位置。

3. If this code ran on a **single-socket** machine with uniform memory, would you still expect a performance difference? Justify your answer. 3. 如果这段代码运行在具有统一内存的**单路**机器上，你是否仍然预计会有性能差异？请说明理由。

### Measure 测量

1. Compile and run the program on a multi-socket machine (or a NUMA-emulated VM): 1. 在多路机器（或 NUMA 模拟虚拟机）上编译并运行该程序：
   ```bash
   g++ -O2 -std=c++17 -o numa_exercise numa_exercise.cpp -lpthread
   ./numa_exercise
   ```

2. Record the wall-clock times printed for both implementations. 2. 记录两种实现输出的墙钟时间。

3. Use `numactl --hardware` to confirm the number of NUMA nodes available. 3. 使用 `numactl --hardware` 确认可用 NUMA 节点的数量。

4. Run the unaware version with all threads pinned to a single socket and compare: 4. 将 unaware 版本的所有线程绑定到单个插槽上运行，并进行比较：
   ```bash
   numactl --cpunodebind=0 --membind=0 ./numa_exercise
   ```

### Fix & Extend 修复与扩展

1. The `sum_numa_aware` function already demonstrates the fix. 1. `sum_numa_aware` 函数已经展示了修复方式。
   Explain *precisely* which line change enforces locality and why it works. 精确说明是修改了哪一行来保证局部性，以及它为什么有效。

2. Modify `sum_numa_unaware` to use `numa_alloc_local()` (from `<numa.h>`) instead of `new`, so each NUMA node allocates its own buffer. 2. 修改 `sum_numa_unaware`，使用 `numa_alloc_local()`（来自 `<numa.h>`）替代 `new`，使每个 NUMA 节点都分配自己的缓冲区。
   Measure again. 再次进行测量。

3. *(Bonus)* Use `pthread_setaffinity_np` to pin each thread to a specific core before it touches memory. 3. *（加分项）* 使用 `pthread_setaffinity_np` 在每个线程访问内存之前将其绑定到特定核心。
   Does explicit affinity improve consistency of results? 显式设置亲和性是否提升了结果的一致性？

## Expected Observations 预期观察结果

On a typical dual-socket machine you should observe the **unaware version running 在典型的双路机器上，你应当会观察到 **unaware 版本的运行速度
20–60% slower** than the aware version at large array sizes (≥ 512 MB), because 比 aware 版本慢 20–60%**，尤其是在大数组规模（≥ 512 MB）下，因为
roughly half the worker threads are performing remote memory accesses for their 大约一半的工作线程在其
entire working set. 整个工作集上都在执行远程内存访问。

## Parallel scan 并行扫描

In this exercise, you'll explore different approaches to implementing parallel prefix sums (scans) and analyze their performance and scalability characteristics. 在本练习中，你将探索实现并行前缀和（scan）的不同方法，并分析它们的性能与可扩展性特征。

While reduction operations combine all elements of a sequence into a single value, scan operations compute all the partial reductions. 虽然归约操作会把一个序列的所有元素合并成单个值，但 scan 操作会计算所有部分归约结果。
For example, given an array `[1, 2, 3, 4, 5]`, an _inclusive_ scan produces `[1, 3, 6, 10, 15]` where each element is the sum of all previous elements including itself. 例如，给定数组 `[1, 2, 3, 4, 5]`，_inclusive_ scan 会得到 `[1, 3, 6, 10, 15]`，其中每个元素都是截至自身为止所有前面元素之和。
An _exclusive_ scan produces `[0, 1, 3, 6, 10]` where each element is the sum of all previous elements excluding itself. 而 _exclusive_ scan 会得到 `[0, 1, 3, 6, 10]`，其中每个元素都是此前所有元素之和，但不包括它本身。

Scans are fundamental parallel primitives with applications in numerous algorithms including sorting, lexical analysis, and string comparison. Scan 是基础的并行原语，在排序、词法分析、字符串比较等大量算法中都有应用。

Consider the sample code given in [`integer-scan`](https://github.com/dssgabriel/TOP-26/lab3/integer-scan). 请参考 [`integer-scan`](https://github.com/dssgabriel/TOP-26/lab3/integer-scan) 中提供的示例代码。

### Sequential implementation 顺序实现

1. Implement the inclusive scan operation sequentially and measure its performance in cycles/element using the `getticks()` function provided in the `"cycle.h"` header. 1. 顺序实现 inclusive scan 操作，并使用 `"cycle.h"` 头文件中提供的 `getticks()` 函数测量其以 cycles/element 表示的性能。

2. Unlike the reduction operation, what is the theoretical computational complexity of a scan? How does this affect parallel implementation strategies? 2. 与归约操作不同，scan 的理论计算复杂度是什么？这会如何影响并行实现策略？

3. Compile and run your sequential implementation with both -O0 and -O3 optimization flags. Compare the performance results. 3. 分别使用 -O0 和 -O3 优化选项编译并运行你的顺序实现，并比较性能结果。

### Parallelization 并行化

4. Parallelize the inclusive scan using OpenMP with just `#pragma omp parallel for`. Verify your results against the sequential version. 4. 仅使用 `#pragma omp parallel for` 通过 OpenMP 并行化 inclusive scan，并将结果与顺序版本对照验证。

5. Why does this approach fail to produce correct results? Explain the data dependency pattern in scan operations that makes them more challenging to parallelize than reductions. 5. 为什么这种方法无法产生正确结果？解释 scan 操作中的数据依赖模式，以及为什么它比归约更难并行化。

### Work-efficient approach 高效工作量方法

6. Implement the work-efficient parallel scan algorithm, which consists of an up-sweep (reduction) phase and a down-sweep phase. 6. 实现高效工作量的并行 scan 算法，它由 up-sweep（归约）阶段和 down-sweep 阶段组成。

7. Use OpenMP tasks or sections to parallelize each phase. Note that synchronization between phases is critical. 7. 使用 OpenMP tasks 或 sections 并行化各个阶段。注意，各阶段之间的同步至关重要。

8. How does the performance compare to the sequential version? What is the theoretical speedup limit for this algorithm? 8. 该算法的性能与顺序版本相比如何？它的理论加速上限是多少？

### Going deeper... 进一步深入……

9. In the naive parallelization attempt, one could try to fix the data race using atomic operations. 9. 在朴素并行化尝试中，可以尝试使用原子操作来修复数据竞争。
   Update your implementation to use `#pragma omp atomic`. 将你的实现更新为使用 `#pragma omp atomic`。
   Is this approach viable for scan operations? 这种方法对 scan 操作可行吗？
   Compare its performance with the other implementations. 将其性能与其他实现进行比较。
   Why are atomic operations generally less effective for scan operations than for reductions? 为什么原子操作通常在 scan 操作中不如在归约中有效？

10. Implement a hybrid approach that combines the work-efficient and blocked methods for larger arrays. What are the trade-offs in choosing block sizes? How does this affect performance across different architectures? 10. 为较大数组实现一种结合高效工作量方法和分块方法的混合方案。选择块大小时有哪些权衡？这会如何影响不同架构上的性能？

11. Implement a blocked parallel scan where: 11. 实现一个分块并行 scan，其中：
  1. The array is divided into blocks;   1. 数组被划分为多个块；
  2. Each block computes its local scan in parallel;   2. 每个块并行计算自己的局部 scan；
  3. The last elements of each block are scanned;   3. 对每个块的最后一个元素再做一次 scan；
  4. The results are propagated back to update each block.   4. 将结果传播回去以更新每个块。

12. What are the limitations of your implementations if you plan to deploy them on many-core architectures like GPUs? 12. 如果你打算将这些实现部署到 GPU 这类多核架构上，它们有哪些局限性？
    How would you need to adapt your algorithms for GPU implementation using frameworks like CUDA or OpenCL? 你需要如何调整算法，才能使用 CUDA 或 OpenCL 等框架在 GPU 上实现？
    Propose a GPU-friendly parallel scan algorithm that addresses these limitations. 请提出一种适合 GPU 的并行 scan 算法来解决这些局限。
