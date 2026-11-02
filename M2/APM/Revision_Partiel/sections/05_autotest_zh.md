## 5 考前自测与法语作答

### 5.1 不看答案先做这十题

以下是根据课程内容编写的自测题，不是往年试卷。先写答案，再看下一节。

1. 用自己的话解释 grid、block、warp、SM 的关系。一个 warp 能否跨两个 block？
2. `N=1000`、每块 `64` 个线程，应启动几个块？实际启动多少线程，有多少线程不更新数据？
3. `gridDim=(2,2,2)`、`blockDim=(4,2,2)`、`blockIdx=(1,0,1)`、`threadIdx=(2,1,0)`。按块优先、块内 x 最快的规则，求唯一线程编号。
4. 行主序矩阵乘法 `A[M,K] * B[K,N] = C[M,N]` 中，线程负责 `(row,col)`，应访问哪些数组元素？
5. 为什么共享内存 tile 的装载后需要同步？下一轮覆盖 tile 前为什么通常也需要同步？
6. `if (i < N) { __syncthreads(); }` 为什么可能错误？
7. 哪种相邻线程访问通常更利于合并：`a[base + tid]` 还是 `a[base + tid * stride]`，其中 `stride` 很大？回答时说明限制条件。
8. 解释 CPU 提交异步 kernel、GPU 完成 kernel、CPU 可以使用输出这三个时刻的区别。一个 `cudaStreamDestroy` 能否代替显式等待？
9. Monte Carlo 的 `512` 个块、每块 `256` 个线程，共需多少个线程结果？每个线程都用完全相同的随机序列会有什么问题？
10. 对 `y[i] += alpha*x[i]` 写出 OpenMP Target 的输入输出映射，说明怎样确认是否在目标设备执行。

### 5.2 答案与检查步骤

1. grid 包含 blocks，block 包含 threads，block 内线程按线性编号组成 warps，SM 是执行线程块的硬件单元。同一 warp 不跨 block；线程块运行先后顺序不能由其编号推定。
2. `ceil(1000/64)=16` 个块，启动 `16*64=1024` 个线程，`24` 个线程被边界判断挡住。
3. 块编号 `5`，每块 `16` 个线程，块内编号 `6`，因此 `5*16+6=86`。这不是按整个空间坐标展平数组后得到的地址。
4. 使用下面的下标。`k` 是内积的循环变量，线程输出边界为 `row<M && col<N`。

```cpp
sum += A[row * K + k] * B[k * N + col];
C[row * N + col] = sum;
```

5. 第一次同步保证其他线程装载的 tile 已经可读；第二次同步防止较快线程用新 tile 覆盖较慢线程仍在使用的数据。只有证明不存在对应依赖时才能去掉某次同步。
6. 边缘块中部分线程可能进入条件、部分不进入。block 级屏障需要参与线程遵守统一到达条件；把越界线程处理成装入零值并让它们同样经过屏障，是共享内存 kernel 的常见写法。
7. 第一个模式通常使相邻 lanes 访问邻近地址，从而减少所需内存事务。具体事务数还取决于元素大小、对齐、活跃 lanes 和硬件，不能只凭源码写死字节数。
8. launch 返回仅说明主机可以继续提交；输出必须等依赖的计算与传输完成才可用。使用正确的 stream/event 等待或相应同步复制建立顺序。销毁 stream 不能代替主机等待其结果。
9. `512*256=131072` 个结果。使用 `double` 时需要 `131072*8=1048576` 字节，即 `1 MiB`。完全相同的随机序列使线程重复采样，不能获得预期的独立样本增益；不同 sequence 是课程代码中的基本处理。
10. 使用 `map(to: x[0:N]) map(tofrom: y[0:N])`。在 target 区域内调用 `omp_is_initial_device()` 检查执行位置；正确结果本身不足以证明 GPU offload 成功。

### 5.3 公式速查与单位

| 要计算的量 | 公式与条件 |
|---|---|
| 一维块数，`N>0` | $G=\lceil N/B\rceil$；正整数代码 `(N+B-1)/B`，注意极大整数溢出 |
| 块内线程数 | $B_x B_y B_z$ |
| 块内线性编号 | $t=t_x+B_x(t_y+B_y t_z)$ |
| 块的线性编号 | $b=b_x+G_x(b_y+G_y b_z)$ |
| 按块展开的全局编号 | $g=b(B_xB_yB_z)+t$ |
| 行主序二维数组 | $\mathrm{index}=row\cdot N+col$，$N$ 为列数 |
| 方阵 GEMM 主项 | $F\simeq 2N^3$ FLOP；完整 $\alpha AB+\beta C$ 的低阶项另计 |
| kernel GFLOP/s | $F/(t_{ms}\cdot10^6)$ |
| 加速比 | $S=T_{CPU}/T_{GPU}$，两者工作量与计时范围应可比较 |
| Monte Carlo | $\widehat\pi=4H/T$，$H$ 为命中数，$T$ 为总样本数 |

字节数先由元素个数乘 `sizeof(type)` 得到。`cudaEventElapsedTime` 的单位是毫秒。GB 和 GiB、GFLOP/s 和 TFLOP/s 不混用。对于独立均匀样本，Monte Carlo 的典型统计误差随总样本数的平方根反比缩小；这不保证每次加样本都更接近真实值。

### 5.4 法语书面答案常用表达

| 想表达的意思 | 可直接使用的法语句子 |
|---|---|
| 先说明存储约定 | On suppose que les matrices sont stockées par lignes. |
| 解释线程职责 | Chaque thread calcule un élément de la matrice résultat. |
| 解释边界判断 | Le test de bornes empêche les threads excédentaires d'accéder hors du tableau. |
| 解释块内屏障 | La barrière garantit que les données chargées par le bloc sont disponibles avant leur utilisation. |
| 区分计时范围 | Le temps mesuré couvre uniquement le kernel ; il exclut les transferts et les allocations. |
| 限定性能结论 | Ce gain dépend de la taille du problème et de la configuration mesurée. |
| 解释合并访存 | Des threads voisins accèdent à des adresses voisines, ce qui favorise la coalescence. |
| 说明结果可用时机 | L'hôte attend la fin du transfert avant de lire le résultat. |

交卷前检查：索引是否越界；整数除法是否意外截断；矩阵行列和 leading dimension 是否一致；屏障是否被所有应参与的线程到达；计时是否真的等到了完成；读改写输出是否保留了初值。
