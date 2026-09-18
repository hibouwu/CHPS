# 优化方案草案 (Optimization Drafts) 20/1

根据代码库分析，以下是针对性能优化与功能扩展的主要方向的可行性分析及实施草案。

## 补充：GEMM 实验与诊断建议 (Post-defense)

### 1. 测量精度与迭代次数 (GEMM)

当前 GEMM 计时在小矩阵上迭代次数较高，而在大矩阵上逐步降低（50/25/12/5），导致统计噪声增大、可比性变差。

* **建议**：统一迭代次数，例如每个实现都固定为 100 次，确保均匀的统计精度。
* **附加**：对每种规模给出均值/方差或置信区间，增强结论可信度。
* **补充**：测试实际网络拓扑中出现的矩阵尺寸，避免只覆盖理想化的尺寸。

### 2. GEMM 对比基线 (BLAS)

* **建议**：引入外部 BLAS 库作为参考（OpenBLAS/MKL/BLIS），对齐相同矩阵尺寸下的性能曲线，用于评估自研实现的优化空间。

### 3. GEMM 进一步瓶颈定位 (Profiling)

* **目标**：明确优化后仍占主导的耗时来源（I/O、内存分配、初始化、算子本身）。
* **建议**：在 GEMM 的热路径与训练主循环中做细粒度 Profiling，基于结果再选择针对性优化（内存/初始化/融合/并行等）。
* **补充**：Profiling 前先将分配与 I/O 完整移出热循环，避免干扰测量结论。

### 4. 小矩阵上的阻塞性能退化分析 (GEMM)

小矩阵上阻塞实现可能慢于 `ikj` 的主要原因包括：

* 三层额外循环带来的控制开销（边界判断、min/max）。
* 内层热循环中存在索引计算（如 `j - jj`），破坏编译器别名分析，导致自动 SIMD 向量化（AVX）失效。

**优化措施**：

* 将循环不变式外提（有效长度、基址指针、偏移计算），简化内层循环，恢复编译器向量化机会。
* 在采用 blocking 前，确认矩阵是否已完全驻留在缓存中；若已在缓存中，blocking 可能没有收益。

## 补充：后续方向 (Advisor Notes)

### 1. GEMM 实验设置

* 增加重复次数，确保单次测量时间达到秒级，提高统计稳定性。
* 覆盖网络拓扑中实际出现的矩阵尺寸。

### 2. Cache Blocking 适用性

* 若矩阵已能完全驻留在缓存中，blocking 可能无收益；应先检查缓存驻留情况再决定是否使用。

### 3. Profiling 前置条件

* 分配与 I/O 应该移出所有热点循环，否则 profiling 结果会被噪声干扰。

### 4. GPU Offload 策略

* 仅将小矩阵 DGEMM 迁移到 GPU 可能无加速，数据传输延迟会掩盖收益。
* 更合理的策略是尽可能将整段计算链条 offload 到 GPU，减少 Host/Device 传输次数。

### 5. HPO 工具建议

* 推荐尝试 `Optuna`：https://optuna.org/

### 6. FP32 与内存优化

* FP32 预期为“免费性能”，且内存复用/避免反复分配的重要性得到确认。

### 7. 进一步研究方向

* 可探索 Federated Learning 相关工作，尝试复现论文结果。
* 可实现卷积层并在更复杂数据集上实验（Fashion-MNIST、CIFAR-10）。

## 方案一：异构计算加速 (GPU/CUDA)

### 1. 现状分析 (GPU)

当前项目使用自定义的 `Matrix` 类（`src/tensor.cpp`）进行 CPU 端的密集矩阵运算，依赖 OpenBLAS 或 OpenMP。数据存储在标准内存中（`std::vector<double>`）。

### 2. 可行性评估 (GPU)

**可行性**：中等（工程成本较高）

* **优势**：`Matrix` 类封装了底层数据与操作，`MathOps` 命名空间隔离了计算图节点的运算逻辑。这使得替换底层计算后端（Backend）相对容易，无需重写上层计算图逻辑。
* **挑战**：需要引入 CUDA 工具链与显存管理（Host/Device 同步），并编写或调用 cuBLAS/cuDNN 算子，同时改造构建系统。

### 3. 实施草案 (GPU)

1. **数据结构改造**：
    * 扩展 `Matrix` 类，增加 `double* device_data_` 指针指向 GPU 显存。
    * 实现 `to_device()` 和 `to_host()` 方法用于显存与内存间的数据传输。
2. **算子迁移**：
    * **矩阵乘法 (GEMM)**：在 `tensor.cpp` 的 `matmul` 实现中增加 `MatmulImpl::Cuda` 分支，底层调用 `cublasDgemm`。
    * **逐元素运算 (Element-wise)**：为加法、ReLU、Sigmoid、Tanh 等编写 CUDA Kernels (`.cu` 文件)。
3. **数据流优化**：
    * 修改 `Trainer::runEpoch`，在 `DataLoader` 读取 Batch 数据后立即传输至 GPU。
    * 确保前馈（Forward）和反馈（Backward）过程中的中间变量尽量常驻 GPU，仅在计算 Loss 标量或评估指标时将必要数据拷回 CPU。

## 方案二：流水线并行 (Pipeline Parallelism)

### 1. 现状分析 (Pipeline)

当前 `Trainer::runEpoch` 采用串行执行模式：
`载入数据 (Load) -> 前馈 (Forward) -> 反馈 (Backward) -> 更新权重 (Update)`
这种模式在 CPU 计算或 I/O 耗时较大时会导致计算单元闲置。

### 2. 可行性评估 (Pipeline)

**可行性**：很高

* 各个阶段在逻辑上边界清晰，易于解耦。
* 主要难点在于多线程环境下的权重一致性（Staleness）控制和资源竞争。

### 3. 实施草案 (Pipeline)

1. **阶段解耦 (Decoupling)**：
    * 定义四个核心接口函数：
        * `Stage1_Load()`: 返回 `BatchData`
        * `Stage2_Forward(BatchData)`: 返回 `LossNode`
        * `Stage3_Backward(LossNode)`: 计算梯度
        * `Stage4_Update()`: 应用梯度
2. **并行策略**：
    * **策略 A：数据预取 (Data Prefetching)**（推荐）
        * 建立一个 `BlockingQueue<BatchData>`。
        * 开启一个独立线程专门执行 `Data Loading`，不断填充队列。
        * 主计算线程从队列取数据进行训练。此方案最稳健，能有效掩盖 I/O 延迟。
    * **策略 B：全流水线 (Full Pipeline)**
        * 使用 4 个线程分别处理 4 个阶段，通过队列传递中间结果。
        * **注意**：此方案会引入“梯度过时”问题（Batch N+1 可能使用尚未更新的权重），属于异步 SGD，需要明确算法取舍。

## 方案三：超参数优化 (HPO)

### 1. 现状分析 (HPO)

`main.cpp` 已具备完善的命令行参数解析功能（`Config` 结构体），支持 `--learning_rate`, `--hidden_sizes`, `--batch_size` 等参数配置。

### 2. 可行性评估 (HPO)

**可行性：很高**
项目非常适合采用“外部驱动”的方式进行 HPO，无需侵入修改 C++ 核心代码。

### 3. 实施草案 (HPO)

1. **外部驱动脚本**：
    * 编写 Python 脚本，使用 `Optuna` 框架。
2. **工作流**：
    * 定义超参搜索空间（如 LR 范围 $10^{-4} \sim 10^{-1}$，Batch Size 32, 64, 128 等）。
    * 脚本通过 `subprocess` 调用编译好的 C++ 可执行文件，传入特定参数组合。
    * C++ 程序将最终测试集准确率输出到标准输出 (stdout) 或 CSV 文件（与现有 `metrics.csv` 统一）。
    * Python 脚本解析输出结果，反馈给优化算法以决定下一组参数。
3. **Optuna 示例 (最小可用)**：
    * 约定 C++ 训练程序在 stdout 输出一行形如：`FINAL_ACC=0.9234`。
    * Python 侧用 `subprocess` 运行并解析该值作为目标函数。

```python
import optuna
import subprocess
import re

def run_trial(trial):
    lr = trial.suggest_float("learning_rate", 1e-4, 1e-1, log=True)
    batch = trial.suggest_categorical("batch_size", [32, 64, 128])
    hidden = trial.suggest_categorical("hidden_sizes", ["128", "128x128", "256x128"])

    cmd = [
        "./ppn_train",
        f"--learning_rate={lr}",
        f"--batch_size={batch}",
        f"--hidden_sizes={hidden}",
        "--epochs=10",
        "--seed=0",
    ]

    out = subprocess.check_output(cmd, text=True)
    m = re.search(r"FINAL_ACC=([0-9.]+)", out)
    if not m:
        raise RuntimeError("FINAL_ACC not found in output")
    return float(m.group(1))

study = optuna.create_study(direction="maximize")
study.optimize(run_trial, n_trials=50)
print("best:", study.best_params, study.best_value)
```

## 方案四：高精度计算优化 (High Performance Computing)

除了架构层面的改动（GPU/流水线），在 CPU 端还有巨大的挖掘空间。

### 1. 降低精度 (HPC - Float)

* **分析**：当前 `tensor.hpp` 中定义 `std::vector<double> data;`，全网使用 64 位双精度浮点数。
* **收益**：
  * **内存带宽翻倍**：同样的总线带宽下，Float (32-bit) 的传输量是 Double 的 2 倍。
  * **SIMD 吞吐翻倍**：AVX2 指令集一次能处理 4 个 double，但能处理 8 个 float。
  * **深度学习足够**：绝大多数神经网络训练仅需 Float32 甚至 Float16 即可收敛。
* **可行性**：**很高**。但可能影响数值稳定性，需要重新做梯度检查与精度验证，再视情况调整学习率等超参。

### 2. 内存复用 (HPC - In-place)

* **分析**：当前 `math_ops.cpp` 中的 `add`, `mul` 都会创建新的 `Matrix` 对象并分配内存：`Matrix out(val_a.rows, val_a.cols);`。对于深度网络，这意味着每层每个 Epoch 都有大量 malloc/free 开销。
* **收益**：减少内存碎片，降低 OS 内存管理开销（Syscall）。
* **实施**：
  * 实现“内存池 (Memory Pool)”或“对象池”。
  * 支持 `a.add_(b)` (in-place) 语义，但需保证反向传播所需的中间值不会被提前覆盖。

### 3. 算子融合 (HPC - Fusion)

* **分析**：目前的 `Linear -> ReLU` 是两个分开的步骤，需要两次内存读写。
* **收益**：将 `MatMul + Bias + ReLU` 融合为一个 Kernel 循环，数据在寄存器或 L1 Cache 中直接流转，大幅减少内存访问。
* **实施**：扩展 `OperationNode`，支持“复合算子”节点，或在 `MathOps` 中增加融合算子分支。

## 方案五：内存分配与初始化优化 (Memory & Initialization Optimization)

### 1. 现状分析 (Memory)

Profiling 显示大量时间消耗在 `std::fill`（底层符号 `__fill_a1`）/ 默认初始化与批量拷贝上。结合源码，主要瓶颈位置如下：

* **重复初始化（双写）**：
  * 位置：`src/tensor.cpp:173` 的 `Matrix::Matrix(size_t,size_t)` 使用 `std::vector<double> data(r*c)`，对 `double` 会进行值初始化（清零）。
  * 位置：`src/mnist_dataset.cpp:46` 构造 `Matrix mat(count, 784)` 后立即用真实数据逐元素覆盖。
  * 结果：同一块内存先清零、再覆盖，产生双倍写入。
* **冗余拷贝（批次搬运）**：
  * 位置：`src/dataloader.cpp:34` 每个 batch 新建 `Matrix x/y`，并用双层循环逐元素拷贝输入与标签。
  * 结果：每个 batch 发生新分配 + 大量元素搬运。
* **无效内存占用（无用 grad_）**：
  * 位置：`src/node.cpp:7` 的 `Node::Node` 无条件分配 `grad_`，即使是不可导的输入/标签节点。
  * 结果：无梯度需求的节点也占用与 value 同等尺寸的内存，并初始化为 0。
* **重复随机化（初始化重复）**：
  * 位置：`src/layer.cpp:6` 构造函数内调用 `randomInit()`。
  * 位置：`src/network.cpp:24-28` 的 `makeLinear()` 又调用一次 `randomInit(...)`。
  * 结果：同一层权重可能被初始化两次。
* **尺寸查询过多（热点循环 size()）**：
  * 位置：`Matrix::add`、`Node::addGrad` 等热点循环中多次调用 `data.size()` 或 `vector::size()`。
  * 结果：函数本身很轻，但调用频率极高（profiling 中 `std::vector<double>::size()` 进入前列）。

### 2. 可行性评估 (Memory)

**可行性**：很高（见效快）
此类优化主要涉及 C++ 代码层面的“瘦身”，无需引入新框架，且能显著降低训练时的 CPU 负载。

### 3. 实施草案 (Memory)

1. **数据加载优化**：
    * **零开销初始化**（对应 `src/tensor.cpp:173`、`src/mnist_dataset.cpp:46`）：
      * 新增 `Matrix(size_t r, size_t c, NoInitTag)` 或 `Matrix::uninitialized(r,c)`，使用未清零的存储（如 `std::unique_ptr<double[]>` 或自管内存）。
      * 在 `MNISTDataset::loadImages` / `loadLabels` 里使用 no-init 构造，然后直接写入数据，避免双写。
    * **减少 Batch 拷贝**（对应 `src/dataloader.cpp:34`）：
      * 方案 A：返回 `BatchView { inputs_, targets_, indices_, range }`，让算子按索引访问原始矩阵，避免物理拷贝。
      * 方案 B：在 `DataLoader` 内部缓存 `batch_x/batch_y`，每次复用同一缓冲区，只更新内容，避免重复分配。
      * 方案 C（索引连续时）：检测连续区间后用 `memcpy`/块拷贝替代逐元素拷贝。
2. **计算图瘦身**：
    * **可选梯度**（对应 `src/node.cpp:7`）：
      * 在 `Node` 中加入 `requires_grad` 标志；仅当需要时才分配 `grad_`。
      * 方案：将 `Matrix grad_` 改为 `std::optional<Matrix>` 或 `std::unique_ptr<Matrix>`，在 `addGrad`/`backward` 首次使用时懒分配。
3. **层初始化修正**：
    * **避免二次 randomInit**（对应 `src/layer.cpp:6`、`src/network.cpp:24-28`）：
      * 方案 A：移除 `LinearLayer` 构造函数中的 `randomInit()`，只在网络构建处显式初始化。
      * 方案 B：在构造函数中接收 `initType/seed` 并初始化一次，`makeLinear()` 不再重复调用。
4. **热点循环微优化**：
    * **缓存 size()**：
      * 在紧密循环前缓存 `const size_t n = data.size();`，避免每次迭代都查询。
    * **减少边界查询**：
      * 在可能的场景中用指针/索引连续访问替代反复 `operator()` 调用，或用循环外缓存 `rows/cols`。
