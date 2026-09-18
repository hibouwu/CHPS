# MLP 与 MNIST 自动微分引擎

[English](../README.md) | [Français](README_fr.md) | **[中文](README_zh.md)** | [العربية](README_ar.md) 

本项目包含了一个使用 C++ 从零编写的多层感知机 (MLP) 神经网络的完整实现。

该项目是**巴黎萨克雷大学 (UVSQ)** 高性能计算与模拟 (CHPS) 硕士一年级课程 **数值编程项目 (PPN)** 的一部分。

项目的主要目标是通过实现自定义的反向模式自动微分引擎和优化矩阵运算，深入理解深度学习框架的内部机制，而不依赖 PyTorch 或 TensorFlow 等外部机器学习库。

## 项目特性

* **自定义自动微分引擎**：支持反向模式自动微分的动态计算图 (DAG) 实现。
* **优化张量运算**：结合缓存分块、OpenMP 多线程及可选 BLAS 集成的矩阵乘法内核。
* **可配置神经网络**：支持任意层配置、激活函数（ReLU, LeakyReLU, GELU, Sigmoid, Tanh）及权重初始化策略（He, Xavier）。
* **训练流水线**：包含 SGD / MomentumSGD / AdamW、交叉熵损失 (CrossEntropy) 和小批量处理 (Mini-batch) 的完整训练循环。

## 环境要求

项目需要符合 C++17 标准的编译器和 CMake。**必须安装 OpenBLAS** 以支持矩阵运算。

* CMake 3.10 或更高版本
* 支持 C++17 的 GCC 或 Clang
* **OpenBLAS** (必需)
* `wget` 和 `gzip` (用于下载数据集)

### 安装依赖

* Fedora / RHEL

```bash
sudo dnf install cmake gcc-c++ openblas-devel wget gzip
```

* Ubuntu / Debian

```bash
sudo apt install cmake g++ libopenblas-dev wget gzip
```

## 编译与使用

### 1. 编译项目

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_MPI=OFF
cmake --build build -j$(nproc)
```

### 1.1 串行版与 MPI 版构建

项目只生成一个训练可执行文件 `ppn_train`。是否启用 MPI 由 CMake 配置阶段的 `-DENABLE_MPI=ON` 决定，不会生成另一个不同名字的可执行文件。

普通单进程构建：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_MPI=OFF
cmake --build build -j$(nproc)
```

启用 MPI 的分布式构建：

```bash
cmake -S . -B build-mpi -DCMAKE_BUILD_TYPE=Release -DENABLE_MPI=ON
cmake --build build-mpi -j$(nproc)
```

建议使用 `build` 和 `build-mpi` 这样的两个不同目录并存保存两套配置。`ENABLE_MPI` 只能在 CMake 配置阶段切换，不能在单独执行 `cmake --build` 时切换。

### 1.2 使用 VTune 构建与打点

如果机器上安装了 Intel VTune Profiler，并且能找到 ITT API 的头文件和库，当前工程会自动启用 VTune task 标记。训练阶段里已经切好了 `train_epoch`、`train_batch`、`data_loader`、`forward_loss`、`backward`、`gradient_sync`、`optimizer_step` 这些区段，直接在 VTune 时间线上就能看到。

推荐构建方式：

```bash
cmake -S . -B build-vtune -DCMAKE_BUILD_TYPE=RelWithDebInfo -DENABLE_VTUNE_MARKERS=ON
cmake --build build-vtune -j$(nproc)
```

如果没有安装 VTune/ITT API，也不会影响正常编译，只是自动关闭这些标记。

### 2. 数据集准备

我们提供了一个脚本来下载 MNIST 数据集：

```bash
./scripts/MnistDDataDownload/get_mnist.sh
```

### 3. 运行程序

使用默认配置训练模型：

```bash
./build/ppn_train --epochs 20 --learning_rate 0.01 --batch_size 64 --hidden_size 128
```

如果构建的是 MPI 版本，则用 `mpiexec` 启动同一个可执行文件：

```bash
mpiexec -n 4 ./build-mpi/ppn_train --epochs 20 --learning_rate 0.01 --batch_size 64 --hidden_size 128
```

### 命令行选项

应用程序支持以下命令行参数：

| 选项 | 默认值 | 说明 |
| -------- | --------- | ------------- |
| `--epochs` | 1 | 训练轮数 (Epochs) |
| `--learning_rate` | 0.01 | 学习率 |
| `--batch_size` | 64 | 小批量大小 (Batch size) |
| `--hidden_size` | 128 | 单个隐藏层的大小 |
| `--hidden_sizes` | "" | 多个隐藏层的大小（逗号分隔，例如 "128,64"）。覆盖 `--hidden_size` |
| `--data_dir` | "mnist" | 包含 MNIST 数据集文件的目录 |
| `--activation` | relu | 激活函数 (relu/leaky_relu/gelu/sigmoid/tanh) |
| `--optimizer` | sgd | 优化器 (sgd/momentum_sgd/momentum/adamw) |
| `--momentum` | 0.9 | 动量系数（用于 momentum_sgd） |
| `--nesterov` | 0 | Nesterov 动量开关（0/1，用于 momentum_sgd） |
| `--weight_decay` | 0.0 | 权重衰减（用于 momentum_sgd/adamw） |
| `--beta1` | 0.9 | AdamW 的 beta1 |
| `--beta2` | 0.999 | AdamW 的 beta2 |
| `--eps` | 1e-8 | AdamW 的 epsilon |
| `--init` | he | 权重初始化策略 (he/xavier/manual) |
| `--seed` | 0 | 随机种子 (0 = 随机) |

## 实用脚本 (Helper Scripts)

`scripts/` 目录下包含了用于基准测试和实验的多种工具：

* **基准测试 (Benchmarks)**：
  * `benchmark_matmul.sh`: 对比朴素矩阵乘法与优化版本的性能。
  * `benchmark_e2e.sh`: 端到端训练性能测试。
* **实验脚本 (Experiments)**：
  * `exp_learning_rate.sh`, `exp_batch_size.sh`, `exp_hidden_size.sh`: 运行超参数扫描。
  * `exp_init_comparison.sh`: 比较不同的权重初始化策略。
* **可视化 (Visualization)**：
  * Python 脚本 (如 `scripts/Utils/plot_metrics.py`) 被 Shell 脚本调用以生成性能对比图。

如果已经安装 VTune，也可以直接用辅助脚本采集热点：

```bash
source /opt/intel/oneapi/setvars.sh
./scripts/Performance/run_vtune_hotspots.sh --epochs 1 --batch_size 256 --data_dir mnist
```

结果会输出到 `output/vtune/`。

## 架构

网络架构基于动态运算图。

```text
输入 (784) -> 线性层 -> ReLU -> 线性层 -> Softmax -> 输出 (10)
```

[查看详细架构图 (UML)](Images/phase4-6.png)

## 性能表现

基准测试在 **AMD Ryzen** 处理器上进行。与朴素实现相比，优化后的 BLAS 版本显示出显著的加速效果。

| 实现版本 | 训练时间 (每轮 epoch) | 加速比 |
| ---------------- | --------------------------- | --------- |
| 朴素 C++ | ~60秒 | 1x |
| **优化版 (BLAS)** | **~0.3秒** | **~200x** |

## 文档

* [**完整技术报告 (PDF)**](../ProjetRapportlatex/rapport.pdf)
* [需求说明书 (中文)](requirements_zh.md)
* 详细设计: [Docs/conception_detaillee_fr.md](conception_detaillee_fr.md)

## 作者

* **石健晔 (Jianye Shi)**
* **钱皓 (Hao Qian)**
* **卞想 (Xiang Bian)**
* **Abdennour Boulmis**

**指导老师**: Aurélien Delval

## 许可证

未提供许可证文件。本项目仅供学术和教育用途。
