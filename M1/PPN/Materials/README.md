# MLP & Autodifferentiation Engine for MNIST

**[English](README.md)** | [Français](Docs/README_fr.md) | [中文](Docs/README_zh.md) | [العربية](Docs/README_ar.md) 

This repository contains a complete implementation of a multi-layer perceptron (MLP) neural network written from scratch in C++.

It was developed as part of the **Numerical Programming Project (PPN)** for the Master 1 CHPS (High Performance Computing & Simulation) curriculum at the **University of Paris-Saclay (UVSQ)**.

The primary objective of this project is to understand the internal mechanisms of deep learning frameworks by implementing a custom reverse-mode autodifferentiation engine and optimized matrix operations without relying on external machine learning libraries like PyTorch or TensorFlow.

## Project Features

* **Custom Autodifferentiation Engine**: A dynamic computation graph (DAG) implementation supporting reverse-mode automatic differentiation.
* **Optimized Tensor Operations**: Matrix multiplication kernels optimized using cache blocking, OpenMP multithreading, and optional BLAS integration.
* **Configurable Neural Network**: Support for arbitrary layer configurations, activation functions (ReLU, LeakyReLU, GELU, Sigmoid, Tanh), and weight initialization schemes (He, Xavier).
* **Training Pipeline**: Complete training loop with SGD / MomentumSGD / AdamW, CrossEntropy loss, and mini-batch processing.

## For Recruiters: Training Systems Highlights

* **Training runtime**: `Trainer::runEpoch`, reverse-mode autograd, optimizers, and explicit profiling phases for `data_loader`, `forward_loss`, `backward`, `gradient_sync`, and `optimizer_step`.
* **Distributed training**: MPI synchronous data-parallel path with `per_param`, `bucketed`, and `overlap_bucketed` gradient synchronization modes using blocking and non-blocking collectives (`MPI_Allreduce` / `MPI_Iallreduce`). The overlap path is treated as correctness-first rather than a finalized high-performance implementation.
* **Data pipeline**: `BatchSource` abstraction for both in-memory MNIST batches and Tiny-ImageNet streaming, including per-batch JPEG decode instead of full-dataset loading.
* **CPU backend**: OpenMP, cache blocking, packing, and GotoBLAS-style AVX2 / AVX-512 GEMM paths as replaceable compute backends.
* **Reproducibility**: CMake build options, benchmark scripts, profiling helpers, and CSV/log outputs under `scripts/` and `output/`.

## Prerequisites

The project requires a C++17 compliant compiler and CMake. OpenBLAS is recommended for optimal performance.

* CMake 3.16 or higher
* GCC or Clang with C++17 support
* OpenBLAS (Optional, but highly recommended)

### Installation

* Fedora / RHEL

```bash
sudo dnf install cmake gcc-c++ openblas-devel
```

* Ubuntu / Debian

```bash
sudo apt install cmake g++ libopenblas-dev
```

## Build and Usage

### 1. Compilation (Default: no gprof overhead)

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_MPI=OFF
cmake --build build -j$(nproc)
```

### 1.1 Serial vs MPI Builds

The project builds a single training executable, `ppn_train`. MPI support is enabled at CMake configure time via `-DENABLE_MPI=ON`; it does not produce a separate executable name.

For a regular single-process build:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_MPI=OFF
cmake --build build -j$(nproc)
```

For a distributed build with MPI enabled:

```bash
cmake -S . -B build-mpi -DCMAKE_BUILD_TYPE=Release -DENABLE_MPI=ON
cmake --build build-mpi -j$(nproc)
```

Using separate build directories such as `build` and `build-mpi` is recommended so you can keep both configurations side by side. The `ENABLE_MPI` option is decided during CMake configuration, not during `cmake --build`.

### 1.2 Profiling Build (gprof only when needed)

`-pg` instrumentation is disabled by default. Enable it explicitly for profiling:

```bash
cmake -S . -B build-gprof -DCMAKE_BUILD_TYPE=Release -DENABLE_GPROF=ON
cmake --build build-gprof -j$(nproc)
```

This keeps normal training runs free from profiling overhead.

### 1.3 VTune Build With ITT Markers

If Intel VTune Profiler and the ITT API development files are available on your machine, the build now auto-detects them and enables task markers for the main training phases (`train_epoch`, `train_batch`, `data_loader`, `forward_loss`, `backward`, `gradient_sync`, `optimizer_step`).

Recommended build:

```bash
cmake -S . -B build-vtune -DCMAKE_BUILD_TYPE=RelWithDebInfo -DENABLE_VTUNE_MARKERS=ON
cmake --build build-vtune -j$(nproc)
```

If the ITT headers or library are not found, the project still builds normally and simply disables VTune markers.

### 1.4 Optional oneDNN Conv Backend

The project now supports an optional oneDNN backend for `Conv2DLayer`. This backend is integrated for correctness first: the external `Matrix<double>` contract stays unchanged, while the internal oneDNN path currently uses an `f32` bridge and writes results back to `double`.

It is not enabled by default and it does not make oneDNN a required project dependency.

Build with oneDNN Conv support:

```bash
cmake -S . -B build-onednn -DCMAKE_BUILD_TYPE=Release -DENABLE_ONEDNN_CONV_BACKEND=ON
cmake --build build-onednn -j$(nproc)
```

Select the Conv backend at runtime:

```bash
./build-onednn/ppn_train --model cnn --conv_backend reference
./build-onednn/ppn_train --model cnn --conv_backend onednn
```

If `--conv_backend onednn` is requested from a binary that was not built with oneDNN Conv support, model construction fails fast instead of silently falling back.

This backend should currently be treated as a correctness-first path, not as a finalized performance path. Primitive caching, weight reorder caching, and cross-layer layout propagation are intentionally not implemented yet. For oneDNN correctness validation, prefer the isolated pure CPU oneDNN container flow rather than changing the default developer environment.

### 2. Dataset Preparation

A script is provided to download the MNIST dataset:

```bash
./scripts/MnistDDataDownload/get_mnist.sh
```

### 3. Execution

To train the model with the default configuration:

```bash
./build/ppn_train --epochs 20 --learning_rate 0.01 --batch_size 64 --hidden_size 128
```

For an MPI-enabled build, launch the same executable through `mpiexec`:

```bash
mpiexec -n 4 ./build-mpi/ppn_train --epochs 20 --learning_rate 0.01 --batch_size 64 --hidden_size 128
```

### Command Line Options

The application supports the following command-line arguments:

| Option | Default | Description |
| -------- | --------- | ------------- |
| `--epochs` | 1 | Number of training epochs |
| `--learning_rate` | 0.01 | Learning rate |
| `--batch_size` | 64 | Mini-batch size |
| `--hidden_size` | 128 | Size of a single hidden layer |
| `--hidden_sizes` | "" | Sizes for multiple hidden layers (comma-separated, e.g., "128,64"). Overrides `--hidden_size`. |
| `--data_dir` | "mnist" | Directory containing MNIST dataset files |
| `--activation` | relu | Activation function (relu/leaky_relu/gelu/sigmoid/tanh) |
| `--optimizer` | sgd | Optimizer (sgd/momentum_sgd/momentum/adamw) |
| `--momentum` | 0.9 | Momentum coefficient (used by momentum_sgd) |
| `--nesterov` | 0 | Nesterov momentum flag (0 or 1, used by momentum_sgd) |
| `--weight_decay` | 0.0 | Weight decay (used by momentum_sgd/adamw) |
| `--beta1` | 0.9 | AdamW beta1 |
| `--beta2` | 0.999 | AdamW beta2 |
| `--eps` | 1e-8 | AdamW epsilon |
| `--init` | he | Weight initialization strategy (he/xavier/manual) |
| `--seed` | 0 | Random seed (0 = random) |
| `--conv_backend` | reference | CNN Conv backend (reference/onednn). `onednn` requires a binary built with `ENABLE_ONEDNN_CONV_BACKEND=ON`. |

## Helper Scripts

The `scripts/` directory contains various utilities for benchmarking and running experiments:

* **Benchmarks**:
  * `benchmark_matmul.sh`: Compare naive vs. optimized matrix multiplication.
  * `benchmark_e2e.sh`: End-to-end training performance test.
* **Experiments**:
  * `exp_learning_rate.sh`, `exp_batch_size.sh`, `exp_hidden_size.sh`: Run hyperparameter sweeps.
  * `exp_init_comparison.sh`: Compare weight initialization strategies.
* **Visualization**:
  * Python scripts (e.g., `scripts/Utils/plot_metrics.py`) are used by the shell scripts to generate performance plots.

### Performance Reproducibility

* Compare MLP vs CNN on fixed settings (`batch=256`, `seed=42`, `MNIST`):

```bash
./scripts/Performance/compare_cnn_mlp.sh
```

This generates logs and a CSV summary at `output/gprof_compare/compare_cnn_mlp.csv`.

* Run CNN gprof pipeline (configure, build, run, export reports):

```bash
./scripts/Performance/run_gprof_cnn.sh
```

This generates `gmon.*`, `gprof_flat.txt`, and `gprof_callgraph.txt` in `output/gprof/`.

* Run a VTune hotspots collection with the helper script:

```bash
source /opt/intel/oneapi/setvars.sh
./scripts/Performance/run_vtune_hotspots.sh --epochs 1 --batch_size 256 --data_dir mnist
```

The script configures a `RelWithDebInfo` build in `build-vtune/`, runs `vtune -collect hotspots`, and stores the result under `output/vtune/`.

## Architecture

The network architecture consists of a dynamic graph of operations.

```text
Input (784) -> Linear -> ReLU -> Linear -> Softmax -> Output (10)
```

[View Detailed Architecture Diagram (UML)](Docs/Images/phase4-6.png)

## Performance

We benchmarked the implementation on an **AMD Ryzen** processor. The optimized BLAS version shows significant speedup compared to the naive implementation.

| Implementation | Training Time (per epoch) | Speedup |
| ---------------- | --------------------------- | --------- |
| Naive C++ | ~60s | 1x |
| **Optimized (BLAS)** | **~0.3s** | **~200x** |

## Documentation

* [Technical Report (French)](ProjetRapportlatex/rapport.pdf)
* Detailed Design: [Docs/conception_detaillee_fr.md](Docs/conception_detaillee_fr.md)
* Requirements (French): [Docs/requirements_fr.md](Docs/requirements_fr.md)

## Authors

* **Jianye Shi**
* **Hao Qian**
* **Xiang Bian**
* **Abdennour Boulmis**

**Supervisor**: Aurélien Delval

## License

No license file is provided. This project is intended for academic and educational use only.
