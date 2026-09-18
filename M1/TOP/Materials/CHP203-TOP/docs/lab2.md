# Lab 2: Memory and data structure layout 实验2：内存与数据结构布局

Software engineering techniques to improve spatial and temporal data locality in the pursuit of performance. 为了追求性能而改进空间与时间数据局部性的软件工程技术。

The code for the exercices is available at [github.com/dssgabriel/TOP-26/lab2](https://github.com/dssgabriel/TOP-26/tree/main/lab2). 本实验代码可在 [github.com/dssgabriel/TOP-26/lab2](https://github.com/dssgabriel/TOP-26/tree/main/lab2) 获取。


## Data structure packing 数据结构紧凑布局

The goal of this exercice is to improve the layout of the data structures used in the `mesh` code. 本练习的目标是改进 `mesh` 代码中所使用数据结构的布局。
We start by packing to reduce its memory footprint. 我们首先通过紧凑化来减少其内存占用。

1. Given the alignment rules imposed on structures/classes by the ISO C and C++ standards, determine how many bytes are 1. 根据 ISO C 和 C++ 标准对结构体/类施加的对齐规则，确定
used by the `Cell` structure. `Cell` 结构体占用了多少字节。

2. Rearrange the layout of the `Cell` structure and delete any unnecessary fields to minimize its memory footprint. 2. 重新安排 `Cell` 结构体的布局，并删除所有不必要的字段，以尽可能减小其内存占用。
Compute how much memory is saved using the optimized layout. 计算优化后布局节省了多少内存。

3. Using Perf, check if there is a change in the number of cache misses between the two structure implementations. 3. 使用 Perf 检查这两种结构实现之间缓存未命中次数是否发生变化。

4. Measure the execution time difference between both implementations of the `Cell` structure. 4. 测量两种 `Cell` 结构实现之间的执行时间差异。

C++ Insights can also show the padding inserted by the compiler in your data structures by enabling the `Show padding information` (see an example [here](https://cppinsights.io/s/197d8cb3)). 通过启用 `Show padding information`，C++ Insights 还可以显示编译器在你的数据结构中插入的填充字节（示例见[这里](https://cppinsights.io/s/197d8cb3)）。


## Array of Structures (AoS) vs. Structure of Arrays (SoA) 结构体数组（AoS）与数组结构（SoA）

Next, we try to improve memory access patterns of the `mesh` code by switching AoS to SoA. 接下来，我们尝试将 `mesh` 代码从 AoS 切换到 SoA，以改进其内存访问模式。

1. Use your prefered tool to determine if the innermost loop in the `Mesh::compute_velocity()` function is correctly vectorized. You can analyze the assembly directely using a disassembler (e.g. `objdump`), or use tools such as Perf or [MAQAO](https://maqao.org/documentation.html) ([CQA module](https://maqao.org/documentation/MAQAO.Tutorial.CQA.pdf)).  1. 使用你偏好的工具判断 `Mesh::compute_velocity()` 函数中最内层循环是否被正确地向量化。你可以直接使用反汇编工具（例如 `objdump`）分析汇编代码，或者使用 Perf 或 [MAQAO](https://maqao.org/documentation.html)（[CQA 模块](https://maqao.org/documentation/MAQAO.Tutorial.CQA.pdf)）等工具。

2. Measure the strong scaling of the current code. Write a small script (can be in bash, Python, R, etc.) to plot the 2. 测量当前代码的强扩展性能。编写一个小脚本（可以使用 bash、Python、R 等）来绘制
results. 结果图。

3. Update the `mesh` code to use SoA instead of AoS. 3. 更新 `mesh` 代码，使其使用 SoA 而不是 AoS。

4. Use the same tools as in question 1 to assert that the change has helped the compiler vectorize the code. 4. 使用与问题 1 相同的工具来确认该修改确实帮助编译器对代码进行了向量化。

5. Measure the strong scaling of the new code. 5. 测量新代码的强扩展性能。

## Dense matrix product optimization 稠密矩阵乘法优化

The rest of this lab is your first lab assignment. Your goal is to improve the performance of a 本实验剩余部分将作为你的第一次实验作业。你的目标是改进一个
naive dense matrix product by tuning array layout and memory access patterns. 朴素稠密矩阵乘法程序的性能，方法是调整数组布局和内存访问模式。

For this exercise, we will rely on [Kokkos](https://kokkos.org/kokkos-core-wiki/index.html) and its [Views](https://kokkos.org/kokkos-core-wiki/ProgrammingGuide/View.html), 在本练习中，我们将依赖 [Kokkos](https://kokkos.org/kokkos-core-wiki/index.html) 及其 [Views](https://kokkos.org/kokkos-core-wiki/ProgrammingGuide/View.html)，
lightweight multidimensional array containers for C++. We will also leverage Kokkos' parallel constructs to express 这是用于 C++ 的轻量级多维数组容器。我们还将利用 Kokkos 的并行构造来表达
portable parallelism. 可移植的并行性。

If you have a GPU (NVIDIA w/ CUDA, AMD w/ HIP, or Intel Arc w/ SYCL), you can also change the Memory/Execution spaces 如果你有 GPU（NVIDIA 使用 CUDA、AMD 使用 HIP，或 Intel Arc 使用 SYCL），你还可以更改内存空间/执行空间
of the code to trivially make it run on your accelerator (see how [here](https://kokkos.org/kokkos-core-wiki/ProgrammingGuide/ProgrammingModel.html)). 以较为直接地让代码运行在你的加速器上（方法见[这里](https://kokkos.org/kokkos-core-wiki/ProgrammingGuide/ProgrammingModel.html)）。

## Array layouts 数组布局

1. Measure the performance of the naive matrix product and plot the results. You can simply measure its runtime, or 1. 测量朴素矩阵乘法的性能并绘制结果图。你可以直接测量其运行时间，或者
derived metrics such as computational performance (in FLOP/s). 从中推导出诸如计算性能（FLOP/s）之类的指标。   
Conduct a strong scaling study and plot the results too. 还要进行强扩展研究并绘制结果图。

2. Try changing the layout of the matrices (e.g. `Kokkos::LayoutRight` to `Kokkos::LayoutLeft`). Do you see any 2. 尝试更改矩阵的布局（例如从 `Kokkos::LayoutRight` 改为 `Kokkos::LayoutLeft`）。你是否观察到
performance improvement? Which combination gives the best results? Explain why. 性能提升？哪种组合效果最好？请解释原因。

3. Repeat the steps of question 1. 3. 重复问题 1 中的步骤。

## Cache blocking 缓存分块

1. Profile the `matrix-product` code using Perf/Hotspot. Specifically, look at cache misses in the L1 and L3 (LLC) caches. 1. 使用 Perf/Hotspot 对 `matrix-product` 代码进行性能分析，特别关注 L1 和 L3（LLC）缓存中的未命中情况。

2. Implement a cache-blocked version of the matrix multiplication to improve the spatial and temporal data locality of 2. 实现矩阵乘法的缓存分块版本，以改善循环中的空间和时间数据局部性。
the loop.

3. Assert that your implementation computes the correct result. Update the `CMakeLists.txt` file accordingly. 3. 确认你的实现能够计算出正确结果，并相应更新 `CMakeLists.txt` 文件。

4. Tune the block dimensions to maximize the performance of your cache-blocked version. Use Perf to assert the 4. 调整块大小以最大化缓存分块版本的性能。使用 Perf 来确认在空间和时间局部性方面的
improvements in spatial and temporal locality. 改进。

5. Make a final performance and strong scaling study of the code and plot the results. Conclude. 5. 对代码进行最终的性能与强扩展研究并绘制结果图，然后给出结论。

## Branch prediction 分支预测

The code in `branch-predict` is not an exercise but a small example showcasing how data ordering can affect performance. `branch-predict` 中的代码不是一道练习题，而是一个用于展示数据排列顺序如何影响性能的小示例。

**What the code does** 代码做了什么

The program allocates two copies of a 5M-element `double` array, both initialized identically with `drand48()` - drawing uniform random values from [0, 1). One copy is left unsorted; the other is sorted ascending via `std::sort`. A third `int` array holds the output. 程序分配了两个包含 500 万个元素的 `double` 数组副本，并使用 `drand48()` 以完全相同的方式初始化，即从 [0, 1) 上均匀抽样随机值。一个数组保持未排序，另一个则通过 `std::sort` 按升序排序。另有一个第三个 `int` 数组用于保存输出结果。

`array_test` iterates over the input and writes `1` or `0` to the result array depending on whether each element is below or above 0.5. Both arrays are processed 31 times each, and wall-clock time is measured separately for each run. `array_test` 会遍历输入数组，并根据每个元素是小于还是大于 0.5，向结果数组写入 `1` 或 `0`。两个数组都会分别被处理 31 次，并对每次运行单独测量墙钟时间。

**The branch at the center of it all** 核心分支

The only non-trivial operation in the hot loop is the comparison `array[i] < 0.5`. Because the input is drawn uniformly from [0, 1), exactly half the values fall below the threshold - making this comparison a fair coin flip on the unsorted array. Modern CPUs speculatively execute past branches using a branch predictor; a misprediction forces a full pipeline flush, wasting about 10-20 cycles per occurrence. At around 50% misprediction rate over 5M iterations x 31 repetitions, this overhead accumulates significantly. 热点循环中唯一真正非平凡的操作就是比较 `array[i] < 0.5`。由于输入数据是从 [0, 1) 上均匀抽样得到的，因此恰好大约有一半元素低于该阈值，这使得在未排序数组上这个比较几乎等同于抛硬币。现代 CPU 会借助分支预测器对分支后的路径进行推测执行；一旦预测失败，就必须清空整个流水线，每次大约浪费 10 到 20 个周期。在 500 万次迭代、重复 31 轮且误预测率接近 50% 的情况下，这种开销会快速累积。

**Why sorting helps** 为什么排序会有帮助

Sorting clusters all sub-0.5 values at the front of the array and all above-0.5 values at the back. The branch pattern becomes: *always taken* for the first half, *never taken* for the second - with a single transition between the two. The predictor locks onto each pattern immediately, reducing mispredictions to near zero. The arithmetic work, memory footprint, and access pattern are otherwise identical between the two runs. 排序会把所有小于 0.5 的值聚集到数组前半部分，把所有大于 0.5 的值放到后半部分。这样一来，分支模式就变成了：前半段几乎总是“跳转成立”，后半段几乎总是“不成立”，两者之间只有一次状态切换。分支预测器可以很快锁定这种模式，从而将误预测次数降到接近零。除此之外，两次运行的算术工作量、内存占用和访问模式都是相同的。

**The takeaway** 结论

This is a clean, controlled demonstration: same data, same operations, same memory layout - only the ordering changes, and with it the predictability of the branch stream. The measurable speedup is **entirely attributable to branch prediction efficiency**. 这是一个非常干净、可控的示例：数据相同、操作相同、内存布局相同，唯一变化的只是数据顺序，以及由此带来的分支流可预测性变化。能够测得的性能提升 **完全可以归因于分支预测效率的提高**。
