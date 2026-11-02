### 3.13 OpenMP Target 与向量加法

10 月 9 日的课表把 OpenMP Target 列入 CM3。[现有课堂示例](../cmexos/ompgpuecAdd.c)计算 `c[i] = a[i] + b[i]`。程序员描述循环和数据，由编译器实现目标设备上的执行与工作分配。

```c
#pragma omp target teams distribute parallel for \
    map(to: a[0:N], b[0:N]) map(from: c[0:N])
for (int i = 0; i < N; ++i) {
    c[i] = a[i] + b[i];
}
```

`target` 定义交给目标设备执行的区域，`teams` 建立线程团队，`distribute` 在团队之间分配循环迭代，`parallel for` 再把迭代分配给团队内的线程。不能把一个 OpenMP 团队与一个 CUDA block 的对应关系当成可移植保证。

在这个没有既有映射的例子中，`map(to: ...)` 让输入数据在设备上可用，`map(from: ...)` 在区域结束时取回输出。`a[0:N]` 表示**从下标 0 开始的 N 个元素**，不是字节数。如果计算 `y[i] = alpha*x[i] + y[i]`，`y` 同时是输入和输出，应使用 `map(tofrom: y[0:N])`。

未使用 `nowait` 时，程序在该 target 区域完成后继续执行。映射子句描述数据可用性；更一般的程序可能已有映射，或设备之间共享存储，因此不应把每个 map 都理解成必定新增一次物理复制。

参考：[OpenMP 5.2 执行模型](https://www.openmp.org/spec-html/5.2/openmpse3.html)、[distribute 构造](https://www.openmp.org/spec-html/5.2/openmpse67.html)、[官方速查卡](https://www.openmp.org/wp-content/uploads/OpenMPRefCard-5-2-web.pdf)。

### 3.14 编译、CPU 回退与代码阅读陷阱

编译通过且结果正确，不能单独证明 GPU 执行成功。目标设备不可用时，OpenMP 实现可能在主机上执行 target 区域。现有示例在区域内检查执行位置：

```c
int on_host = 1;
#pragma omp target map(from: on_host)
{
    on_host = omp_is_initial_device();
}
```

`on_host != 0` 表示初始设备，即本程序中的主机。零值表示目标设备，其具体类型由环境决定。编译选项必须配置可用的 offload 目标；只加 `-fopenmp` 不能保证生成并使用 GPU 代码。

如果连续几个循环使用同一批数组，可以用 `target data` 让映射跨区域保留，减少重复传输。无论怎样安排，仍需明确每个数据由哪个区域产生、何时才能使用。

**典型题。** AXPY 更新为何不能只写 `map(from: y[0:N])`？因为计算需要 `y` 的初值；在没有既有映射时，还必须把初值放到设备可用的位置。为何 `#pragma omp parallel for` 不足以表达 GPU offload？因为它在当前执行环境中分配线程工作，本身没有建立 target 区域。

参考：[omp_is_initial_device](https://www.openmp.org/spec-html/5.0/openmpsu149.html)。
