# ARCHITECTURE ET PROGRAMMATION D’ACCÉLÉRATEURS MATÉRIELS

*Lecture 1 : Archirecture and programming models*

> 本文由教师 PDF 自动提取，已整理本地图片并校正部分明确的识别错误。幻灯片的逐步展示会造成内容重复；代码和公式请以同名 PDF 为准。

**Enseignant :** Julien Jaeger · julien.jaeger@cea.fr

**PDF source :** [APM_Cours1_2025.pdf](Archive/APM_Cours1_2025.pdf)（93 页旧版）

> 版本说明（2026-09-25）：本提取稿保留旧版正文，不包含新版新增内容。今年的 96 页课件见 [APM_Cours1_en.pdf](APM_Cours1_en.pdf)，增量同步后的中文讲义见 [APM_Cours1_zh.md](APM_Cours1_zh.md)。

## Introduction

### Theme : accelerators

- State-of-the-art
- Accelerators architecture
- Accelerators programming
- Specific optimizations

### Prerequisites

- Basic notions in computer architecture
- Imperative programming (especially C)
- Notion in parallel programming

### General outline

**Goal:**

- Introduction to accelerators
- Expertise in CUDA programming

**Outline:**

- Architecture
- Porgramming models
- Introduction to CUDA

**Teachers:**

- Julien Jaeger (julien.jaeger@cea.fr)
- Thibaut Pepin (thibaut.pepin@cea.fr)
- Cedric Chevalier (cedric.chevalier@cea.fr)

**Lecture 1 outline:**

- Overview of existing accelerators
- Nvidia GPU architectures: Kepler, Volta, Ampere, Grace+Hopper
- Overview of programming models for accelerators
- NVIDIA CUDA (part 1)

## OVERVIEW OF ACCELERATORS

### Accelerators

### Definition:

- A distinct resource (located on the same chip as the main processor or not) designed for different objectives than the central processor.
**In short:**

- A processor dedicated to a special class of applications.
- Allows for better performance in its domain of expertise.

### Accelerators – Interconnection

- Accelerators are attached to the processor(s) via an interconnect link.

**Behavior similar to a peripheral device:**

- The central processor controls access.
- It also executes the main part of the code.

**Several types of interconnections:**

- Off-chip accelerators
- On-chip accelerators

### Types of connections

**Via the system bus:**

- Nvidia GPGPU, Intel MIC

**Advantages:**

- Low cost
- Easy integration
**Drawbacks:**

- Modest performance due to the generic nature of the bus
- Suboptimal bandwidth and latency

**Via the processor bus:**

- IBM Cell, AMD APU, ARM Grace + Nvidia Hopper

**Advantages:**

- Fast access
- Possibility to share resources with the CPU

**Drawbacks:**

- Complex integration
- Dependency on the processor

### Accelerator Architecture

### Microarchitecture:

- Driven by the diversity of applications to be executed and the domain of expertise.
- Simplification compared to CPUs
- (out-of-order execution, branch prediction, etc.).

**Exploited Parallelism:**

- Generally fine-grained.
- Most exploit a form of Single Instruction Multiple Data (SIMD).
**But:**

- Significant part of the work is left to the software stack and developers.

### Accelerator Architecture

### Memory Hierarchy:

- Software-controlled memory (scratchpad memory).
- Hardware-managed cache (like a general-purpose CPU).
- Hardware interconnection between different compute processors.
- High bandwidth between the accelerator and global memory.

### Summary:

- Interesting possibilities for high-performance computing.
- But many aspects need to be managed manually.
- This directly influences how accelerators are programmed.

### Accelerator Programming

- View of an accelerator as a worker peripheral.
- The main processor controls access to specialized computing resources:
- Main processor (CPU): host
- Accelerator: device

**General Concepts:**

- Data transfers
- Execution of offloaded code in a different language
- Manual execution management
- Querying the accelerator for its status
- Retrieving data back to the host

### Overview of Accelerators

### Dedicated accelerators

- Cell (IBM)
- MIC or Xeon Phi (Intel)
- Graphics processors
- NVIDIA
- AMD/ATI
- Reconfigurables architectures
- FPGA

### CELL processor (IBM)

![Cours 1 图 001](Images/cours1_img_001.jpg)

- Developed jointly by IBM, Sony, and Toshiba (2005+).

**8 64-bit floating-point cores:**
- Called Synergistic Processor Elements (SPEs).
- One master 64-bit PowerPC processor capable of executing two threads.
- SPEs can process 128-bit operands, decomposed into four 32-bit words (SIMD).
- MIC & Xeon Phi (Intel)

**Accelerator proposed by Intel:**

- Many-Integrated Core (MIC).

**Architecture:**

- x86 cores
- Hyperthreading support
- Cache coherence
- First version: KNF (2010)
- Latest version: KNL (2013) & KNM (2017)

### KNL

### KNL Overview

![Cours 1 图 002](Images/cours1_img_002.jpg)

- Chip: 36 Tiles interconnected by 2D Mesh Tile: 2 Cores + 2 VPU/core + 1 MB L2
- Memory: MCDRAM: 16 GB on-package; High BW DDR4: 6 channels @ 2400 up to 384 GB IO: 36 lanes PCle* Gen3. 4 lanes of DMI for chipset Node: 1-Socket only Fabric: Intel® Omni-Path Architecture on-package (not shown)
- Vector Peak Perf: 3+TF DP and 6+TF SP Flops ~5X Higher BW Scalar Perf: ~3x over Knights Corner than DDR Streams Triad (GB/s): MCDRAM : 400+; DDR: 90+
- Source Intel: All products, computer systems, dates and figures specified are preliminary based on current expectations, and are subject to change without notice, KNL data are preliminary based on current expectations and are subiect to change without notice. 1Binary Compatible with Intel Xeon processors using Haswell Instruction Set (except TSX). 2Bandwidth numbers are based on STREAM-like memory access pattern when MCDRAM used as flat memory. Results have been estimated based on internal Intel analysis and are provided for informational purposes only. Any difference in system hardware or software design or configuration may affect actual performance. *Other names and brands may be claimed as the property of others

![Cours 1 图 003](Images/cours1_img_003.jpg)

### Graphics Processors

- Graphics cards initially for 2D and 3D display on screens:
- Dedicated graphics processor(s).

**Impressive computing capabilities:**

- Optimized for image rendering (different objectives from generalpurpose processors).
- Ideal for processing regular data.

**Use for scientific computing:**

- GPGPU (General Purpose Graphics Processing Unit).

### GPGPU

**Graphics cards on a system bus:**

- Interconnection on the motherboard.
- Communications via the PCI-express port.

**Possibility to connect multiple graphics cards:**

- Multi-GPU programming.
- Currently used in heterogeneous supercomputers.

### Nvidia Fermi Architecture (2010)

![Cours 1 图 004](Images/cours1_img_004.jpg)

![Cours 1 图 005](Images/cours1_img_005.jpg)

- Nvidia Volta Architecture (2017)

![Cours 1 图 006](Images/cours1_img_006.jpg)

![Cours 1 图 007](Images/cours1_img_007.jpg)

![Cours 1 图 008](Images/cours1_img_008.jpg)

### ATI Cypress Architecture (2009)

![Cours 1 图 009](Images/cours1_img_009.jpg)

- Set of vector units: SIMD Engines.
- Memory hierarchy: L2 Cache.

**Peak performance:**

- 2.72 TFlops SP
- 0.54 TFlops DP

![Cours 1 图 010](Images/cours1_img_010.jpg)

### ATI Radeon Navi Architecture (2019)

### AMD Fusion Llano Architecture (2011)

![Cours 1 图 011](Images/cours1_img_011.jpg)

![Cours 1 图 012](Images/cours1_img_012.jpg)

- Nom de code de l’architecture d’AMD/ATI : Fusion
- Design d’un APU (Accelerator Processing Unit)

**Sur la même puce :**

- CPU
- Accélérateur de type GPU
- Première génération disponible en 2011
- Llano avec technologie Bulldozer ou Bobcat
- http://fusion.amd.com

### AMD APU Picasso Architecture

### Ryzen-bridge 2019

![Cours 1 图 013](Images/cours1_img_013.jpg)

### AMD APU Picasso Architecture

### Ryzen-bridge 2019

![Cours 1 图 014](Images/cours1_img_014.jpg)

### AMD MI300 – Frontier (2023)

![Cours 1 图 015](Images/cours1_img_015.jpg)

![Cours 1 图 016](Images/cours1_img_016.jpg)

### AMD MI300 – Frontier (2023)

![Cours 1 图 017](Images/cours1_img_017.jpg)

![Cours 1 图 018](Images/cours1_img_018.jpg)

### Nvidia Grace+Hopper (2022)

![Cours 1 图 019](Images/cours1_img_019.jpg)

### Nvidia Grace+Hopper (2022)

![Cours 1 图 020](Images/cours1_img_020.jpg)

### Evolution of accelerators in the Top500

![Cours 1 图 021](Images/cours1_img_021.jpg)

### Evolution of accelerators in the Top500

![Cours 1 图 022](Images/cours1_img_022.jpg)

![Cours 1 图 023](Images/cours1_img_023.jpg)

## NVIDIA GRAPHICS CARD ARCHITECTURE

### NVIDIA GeForce Architecture

### Basic Building Block:

- Very simple compute core.
- Set of compute cores grouped in a stream multiprocessor.

### Why "stream"?

- Designed to operate on a continuous data stream.
- Synchronous language on each multicore.

### Design for Fine-Grained Parallelism

### Nvidia Kepler Architecture (2012)

![Cours 1 图 024](Images/cours1_img_024.jpg)

### 15 Streaming Multiprocessors (SMs).

- Arrangement perpendicular to the shared L2 cache.

### Legend:

- Green: Compute core (double precision unit in orange).
- Orange: Scheduler and dispatcher.
- Light blue: Register bank and L1 cache.

![Cours 1 图 025](Images/cours1_img_025.jpg)

![Cours 1 图 026](Images/cours1_img_026.jpg)

![Cours 1 图 027](Images/cours1_img_027.jpg)

### Kepler : Streaming Multiprocessor

![Cours 1 图 028](Images/cours1_img_028.jpg)

- Streaming Multiprocessor (SMX).

**192 CUDA-compatible cores:**

- ALU unit.
- Single-precision floating-point unit.
- 64 double-precision floatingpoint units.
- 32 special units (SFU).
- 32 load/store units.

![Cours 1 图 029](Images/cours1_img_029.jpg)

![Cours 1 图 030](Images/cours1_img_030.jpg)

### Kepler : Streaming Multiprocessor

![Cours 1 图 031](Images/cours1_img_031.jpg)

### SIMT execution type:

- Single-Instruction Multiple Thread.
- Similar to SIMD.
- Synchronous execution of compute cores.

**Each SMX manages and executes compute threads in batches of 32:**

- Notion of warp.
- 4 warp schedulers per SMX.

![Cours 1 图 032](Images/cours1_img_032.jpg)

### Kepler: Memory Hierarchy

- Thread scheduled on a compute core on an SMX.
- Memory access via load or store instruction.

**Two possibilities:**

- Access to shared memory: no cache.
- Access to global device memory: passes through two levels of cache.
- Physically, the same memory is used for L1 cache and shared memory:
- Appearance of a read-only cache (48 KB).

![Cours 1 图 033](Images/cours1_img_033.jpg)

![Cours 1 图 034](Images/cours1_img_034.jpg)

- 6 GPCs (Graphics Processing Clusters).
- 7 TPCs (Texture Processing Clusters) per GPC.
- 2 SMs per TPC.
- Total: 2 * 7 * 6 = 84 SMs!

![Cours 1 图 035](Images/cours1_img_035.jpg)

- 5376 single-precision floating-point units (14 Tflops) and same amount of integer units.
- 2688 double-precision floating-point units (7 Tflops).
- 672 tensor cores (112 Tflops).
- + 336 texture units.

### Nvidia Ampere (2020)

![Cours 1 图 036](Images/cours1_img_036.jpg)

- 8 GPCs (Graphics Processing Clusters).
- 8 TPCs (Texture Processing Clusters) per GPC.
- 2 SMs per TPC.
- Total: 2 * 8 * 8 = 128 SMs!

### Nvidia Ampere: SM view

- 4 processing blocks per SM.
- 16 INT units: 8192 (21 Tops).
- 16 single-precision floating-point units: 8192 (21 Tflops).
- 8 double-precision floating-point units: 4096 (10 Tflops).
- 1 tensor core (112 Tflops).

![Cours 1 图 037](Images/cours1_img_037.jpg)

![Cours 1 图 038](Images/cours1_img_038.jpg)

- 8 GPCs (Graphics Processing Clusters).
- 9 TPCs (Texture Processing Clusters) per GPC.
- 2 SMs per TPC.
- Total: 2 * 9 * 8 = 144 SMs!

### Hopper : SM view

**4 × Processing Blocks:**

- 16 INT32 units.
- 32 single-precision units.
- 16 double-precision units.
- 8 load/store units.
- 1 warp scheduler.
- 1 dispatch unit.
- Maximum 64 active warps.

![Cours 1 图 039](Images/cours1_img_039.jpg)

![Cours 1 图 040](Images/cours1_img_040.jpg)

### Hopper Performance

**"Classical" computing:**
- FP32: 60 Tflops. FP64: 30 Tflops.

**"AI" computing (tensor cores):**
- FP64: 60 Tflops. TF32: 1 Pflops. FP16: 2 Pflops. FP8: 4 Pflops.

**Difference between FP32 and TF32:**

### Grace-Hopper Superchip: The Future?

![Cours 1 图 041](Images/cours1_img_041.jpg)

**"Grace" processor:**

- ARM Neoverse V2 architecture.
- 72 cores.

**CPU and GPU on the same die to accelerate data transfers:**

- 2x 450GB/s.
- Native unified memory guaranteed by a memory coherence system (C2C).

![Cours 1 图 042](Images/cours1_img_042.jpg)

- Beware of NUMA effects!

![Cours 1 图 043](Images/cours1_img_043.jpg)

![Cours 1 图 044](Images/cours1_img_044.jpg)

## MODÈLES DE PROGRAMMATION POUR ACCÉLÉRATEURS

### Programming Models

### Dedicated Languages:

- Close To Metal (CTM), HIP/ROCm, CUDA.
- Portable Languages:
- X Low-level languages OpenCL.
- Directives based: OpenMP, OpenACC.

**4A High-Level Languages / DSLs:**

- Kokkos, Legion, RAJA, SYCL

### ATI/AMD Programming

### Close to Metal (CTM) / CAL/IL:

- Very low level.
- Rarely used now.

**HIP/ROCm:**

- Provides a toolkit for writing GPU code and translating CUDA code to HIP.

**OpenCL/SYCL:**

- Supports OpenCL and SYCL standards.
- AMD/ATI is part of the consortium.
- To be continued...

![Cours 1 图 045](Images/cours1_img_045.jpg)

![Cours 1 图 046](Images/cours1_img_046.jpg)

### Directives de parallélisation

- Proposal for directive-based programming:
- Adding #pragma (C, C++) in sequential code.
- Possibility to add these directives in already parallel code (MPI, OpenMP, etc.): depends on the model.

**Proposed solutions:**

- OpenACC
- OpenMP 4+

**Advantages:**

- Portability depending on the accelerators.
- Original (or even sequential) semantics can be preserved.

**Drawbacks:**

- Often need to finish "by hand".
- Sometimes limited scope.

## NVIDIA CUDA

### According to you…

- What do you think we will find in a GPU program?
- Which parts?
- Which steps?

### Overview

- Two parts: host program and compute kernels.
- Need to transfer data between hosts and devices.
- Dedicated compilation chain due to compute kernels (different language).
- Link with a runtime (user space) and a driver (kernel space).

### Programming Scheme

1. Initialization on host: memory allocation, reading inputs, etc.
2. Memory allocation on the GPU: manual management.
3. Transfer host → GPU.
4. Execution of a compute kernel: multiple kernels may be launched.
5. Transfer GPU → host.
6. Free GPU memory.
7. Free CPU memory.

![Cours 1 图 047](Images/cours1_img_047.jpg)

![Cours 1 图 048](Images/cours1_img_048.jpg)

### Comment compiler ?

### Code Structure:

- Part for the host.
- Part for the device.
- In practice, these codes can be mixed in the same file.
- Host Programming: C or C++.
- Device Programming: CUDA (superset of C99 standard).

**Compilation Chain: NVCC:**

- As a programmer: use the nvcc compiler.
- Do not hesitate to check the documentation provided with the SDK.

### Example Program

- Example: Adding 2 vectors.

**Basic operation:**

- c[i] = a[i] + b[i].

```text
How to program this compute kernel sequentially?
```

- Simple loop.
- Apply the basic operation to each element.

```cpp
void vectAdd(
    double * a, double * b,
    double * c, int N) {
    int i;
    for (i=0;i<N;i++) {
    c[i] = a[i] + b[i]
    }
}
```

```cpp
void vectAdd(
    double * a, double * b,
    double * c, int N) {
    int i;
    for (i=0;i<N;i++) {
    c[i] = a[i] + b[i]
    }
}
```

- Transfert du tableau c
- Transfert du tableau a
- Transfert du tableau b
- Transfert de l’entier N
- Transfert du tableau c
- Exécution sur le GPU (en parallèle ??)
- Porting Our Example
- Transfert du tableau a
- Transfert du tableau b
- Transfert de l’entier N
- Transfert du tableau c
- Exécution sur le GPU (en parallèle ??)

![Cours 1 图 049](Images/cours1_img_049.jpg)

- Rapatriement du tableau c
- Transfert du tableau a
- Transfert du tableau b
- Transfert de l’entier N

### Host Programming

### Host (Central CPU) Management:

- Need to manage GPU memory.
- Need to transfer data.
- Gives the order to execute the kernel.
- CUDA Host API:
- High-level/low-level CUDA.
- cudaMalloc: Allocate data on the device.
- cudaMemcpy: Transfer data to the device or to the host.

> 校注：下面对应原 PDF 第 61–67 页逐步展示的双栏示例。自动提取将页眉、注释和左右栏混入代码块；这些代码块仅用于对照幻灯片，不能直接编译运行。

```text
Host program
GPU
void vectAdd(
    double * a, double * b, double * c,
    int N) {
    double * d_a;
    double * d_b;
    double * d_c;
    cudaMalloc((void **)&d_a,
    N*sizeof(double));
    cudaMalloc((void **)&d_b,
    N*sizeof(double));
    cudaMalloc((void **)&d_c,
    N*sizeof(double));
    cudaMemcpy(d_a, a, N*sizeof(double),
    cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N*sizeof(double),
    cudaMemcpyHostToDevice);
    vectAddKernel(d_a, d_b, d_c, N);
    cudaMemcpy(c, d_c, N*sizeof(double),
    cudaMemcpyDeviceToHost);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    61
GPU
```

```text
Host program
GPU
void vectAdd(
    double * a, double * b, double * c,
    int N) {
    double * d_a;
    double * d_b;
    double * d_c;

    cudaMalloc((void **)&d_a,
    N*sizeof(double));
    cudaMalloc((void **)&d_b,
    N*sizeof(double));
    cudaMalloc((void **)&d_c,
    N*sizeof(double));

Device pointers
    cudaMemcpy(d_a, a, N*sizeof(double),
    cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N*sizeof(double),
    cudaMemcpyHostToDevice);

    vectAddKernel(d_a, d_b, d_c, N);

    cudaMemcpy(c, d_c, N*sizeof(double),
    cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

GPU
62
GPU
```

```text
Host program
GPU
void vectAdd(
    double * a, double * b, double * c,
    int N) {
    double * d_a;
    double * d_b;
    double * d_c;

    cudaMalloc((void **)&d_a,
    N*sizeof(double));
    cudaMalloc((void **)&d_b,
    N*sizeof(double));
    cudaMalloc((void **)&d_c,
    N*sizeof(double));

    cudaMemcpy(d_a, a, N*sizeof(double),
    cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N*sizeof(double),
    cudaMemcpyHostToDevice);

    vectAddKernel(d_a, d_b, d_c, N);

    cudaMemcpy(c, d_c, N*sizeof(double),
    cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    GPU
    Memory allocation on the device
63
```

```text
Host program
GPU
void vectAdd(
    double * a, double * b, double * c,
    int N) {
    double * d_a;
    double * d_b;
    double * d_c;

    cudaMalloc((void **)&d_a,
    N*sizeof(double));
    cudaMalloc((void **)&d_b,
    N*sizeof(double));
    cudaMalloc((void **)&d_c,
    N*sizeof(double));

Data transfers from host to device
    cudaMemcpy(d_a, a, N*sizeof(double),
    cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N*sizeof(double),
    cudaMemcpyHostToDevice);

    vectAddKernel(d_a, d_b, d_c, N);

    cudaMemcpy(c, d_c, N*sizeof(double),
    cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

64
GPU
```

```text
Host program
GPU
void vectAdd(
    double * a, double * b, double * c,
    int N) {
    double * d_a;
    double * d_b;
    double * d_c;

    cudaMalloc((void **)&d_a,
    N*sizeof(double));
    cudaMalloc((void **)&d_b,
    N*sizeof(double));
    cudaMalloc((void **)&d_c,
    N*sizeof(double));

    cudaMemcpy(d_a, a, N*sizeof(double),
    cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N*sizeof(double),
    cudaMemcpyHostToDevice);

    vectAddKernel(d_a, d_b, d_c, N);

    cudaMemcpy(c, d_c, N*sizeof(double),
    cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    void vectAdd(
    double * a, double * b, double * c,
    int N) {
    double * d_a;
    double * d_b;
    double * d_c;

    kernel invocation
  (will execute on the device)

    65
GPU
```

```text
Host program
GPU
void vectAdd(
    double * a, double * b, double * c,
    int N) {
    double * d_a;
    double * d_b;
    double * d_c;

    cudaMalloc((void **)&d_a,
    N*sizeof(double));
    cudaMalloc((void **)&d_b,
    N*sizeof(double));
    cudaMalloc((void **)&d_c,
    N*sizeof(double));

    data transfer from device to host
    cudaMemcpy(d_a, a, N*sizeof(double),
    cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N*sizeof(double),
    cudaMemcpyHostToDevice);

    vectAddKernel(d_a, d_b, d_c, N);

    cudaMemcpy(c, d_c, N*sizeof(double),
    cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    data transfer from device to host
    data transfer from device to GPU
66
```

```text
Host program
GPU
void vectAdd(
    double * a, double * b, double * c,
    int N) {
    double * d_a;
    double * d_b;
    double * d_c;

    cudaMalloc((void **)&d_a,
    N*sizeof(double));
    cudaMalloc((void **)&d_b,
    N*sizeof(double));
    cudaMalloc((void **)&d_c);
    N*sizeof(double));

    cudaMemcpy(d_a, a, N*sizeof(double),
    cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N*sizeof(double),
    cudaMemcpyHostToDevice);

    vectAddKernel(d_a, d_b, d_c, N);

    cudaMemcpy(c, d_c, N*sizeof(double),
    cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    free memory allocated on device
67
GPU
```

### Execution model

- Now remains to execute the kernel on the device
- How to program the following code on the device ?

$$
\text { for } (i = 0; i <   N; i + +)
$$

$$
c [ i ] = a [ i ] + b [ i ];
$$

### Execution model

- Now remains to execute the kernel on the device
- How to program the following code on the device ?

$$
\text { for } (i = 0; i <   N; i + +)
$$

$$
c [ i ] = a [ i ] + b [ i ];
$$

- The CUDA model is a model based on threads
- At invocation of a kernel, launches a bunch of threads
- Each thread executes the kernel
- Quite similar to passing the kernel function to several pthread_create invocations
- CUDA programming is multithreaded
- Need to think per thread, and not per loop or loop iteration

### Execution model

- Now remains to execute the kernel on the device
- How to program the following code on the device ?

$$
\text { for } (i = 0; i <   N; i + +)
$$

$$
c [ i ] = a [ i ] + b [ i ];
$$

- The CUDA model is a model based on threads
- At invocation of a kernel, launches a bunch of threads
- Each thread executes the kernel
- Quite similar to passing the kernel function to several pthread_create invocations
- CUDA programming is multithreaded
- Need to think per thread, and not per loop or loop iteration

**Code du kernel dans notre cas :**

```cpp
int i = index; /* Update i with thread index */ c[i] = a[i] + b[i];
```

### Threads hierarchy

- How to Know the Identifier of a Thread?
- This is related to the organization of threads within the CUDA execution model.
- CUDA defines the concepts of blocks and grids to hierarchically organize threads:
- A grid contains blocks.
- A block contains threads.
- Both grids and blocks can have 1 to 3 dimensions (logical representation, not physical).
- In Practice ?

### Threads hierarchy

### Example with

- A grid with blocks organized in 2D
- 6 blocks with threads also in 2D
- 6 blocks in the grid with 12 threads per block
-  72 threads in total
- How to find a thread index ?
- 2D array linearization

![Cours 1 图 050](Images/cours1_img_050.jpg)

### Threads hierarchy

### CUDA defines several variables in the kernel

- gridDim : Contains the number of blocks in each dim
- blockIdx : Contains the coordinates of the block in the grid for the three dimensions
- blockDim : Contains the number of threads in each dim
- threadIdx : Contains the coordinates of the thread in its block for the three dimensions

**The type of these variables is a CUDA specific type:**

- dim3

![Cours 1 图 051](Images/cours1_img_051.jpg)

- It has three fileds : {x, y, z} for values on each dimension

![Cours 1 图 052](Images/cours1_img_052.jpg)

### Threads hierarchy

![Cours 1 图 053](Images/cours1_img_053.jpg)

### Threads hierarchy

### Let’s compute the index of the chosen thread

- BlockIdx.x = 1 ; BlockIdx.y = 0
- GridDim.x = 3 ; GridDim.y = 2

![Cours 1 图 054](Images/cours1_img_054.jpg)

### Threads hierarchy

- Let’s compute the index of the chosen thread
- BlockIdx.x = 1 ; BlockIdx.y = 0

```text
GridDim.x = 3 ; GridDim.y = 2
```

```text
Block_glob_id = BlockIdx.y x GridDim.x + BlockIdx.x = 0 x 3 + 1 = 1
```

![Cours 1 图 055](Images/cours1_img_055.jpg)

### Threads hierarchy

- Let’s compute the index of the chosen thread

```text
BlockIdx.x = 1 ; BlockIdx.y = 0
```

```text
GridDim.x = 3 ; GridDim.y = 2
```

```text
Block_glob_id = BlockIdx.y x GridDim.x + BlockIdx.x = 0 x 3 + 1 = 1
BlockDim.x = 4
BlockDim.y = 3
```

![Cours 1 图 056](Images/cours1_img_056.jpg)

```text
Block_glob_id = BlockIdx.y x GridDim.x + BlockIdx.x = 0 x 3 + 1 = 1
BlockDim.x = 4
BlockDim.y = 3
```

### Threads hierarchy

- Let’s compute the index of the chosen thread

```text
BlockIdx.x = 1 ; BlockIdx.y = 0
```

```text
GridDim.x = 3 ; GridDim.y = 2
```

```text
✿ Nb_threads_per_block = BlockDim.x x BlockDim.y = 4 x 3 =12
```

![Cours 1 图 057](Images/cours1_img_057.jpg)

```text
Let's compute the index of the chosen thread
    BlockIdx.x = 1 ; BlockIdx.y = 0
    GridDim.x = 3 ; GridDim.y = 2
    Block_glob_id = BlockIdx.y x GridDim.x + BlockIdx.x = 0 x 3 + 1 = 1
    BlockDim.x = 4
    BlockDim.y = 3
    Nb_threads_per_block = BlockDim.x x BlockDim.y = 4 x 3 = 12
    threadIdx.x = 1
    threadIdx.y = 2
    BlockDim.x = 4
```

### Threads hierarchy

![Cours 1 图 058](Images/cours1_img_058.jpg)

### Threads hierarchy

```text
Let's compute the index of the chosen thread
    BlockIdx.x = 1; BlockIdx.y = 0
    GridDim.x = 3; GridDim.y = 2
    Block_glob_id = BlockIdx.y x GridDim.x + BlockIdx.x = 0 x 3 + 1 = 1
    BlockDim.x = 4
    BlockDim.y = 3
    Nb_threads_per_block = BlockDim.x x BlockDim.y = 4 x 3 = 12
    threadIdx.x = 1
    threadIdx.y = 2
    BlockDim.x = 4
    Thread_loc_id = threadIdx.y x BlockDim.x + threadIdx.x = 2 x 4 + 1 = 9
```

![Cours 1 图 059](Images/cours1_img_059.jpg)

### Threads hierarchy

```text
Let's compute the index of the chosen thread
    BlockIdx.x = 1 ; BlockIdx.y = 0
    GridDim.x = 3 ; GridDim.y = 2
    Block_glob_id = BlockIdx.y x GridDim.x + BlockIdx.x = 0 x 3 + 1 = 1
    BlockDim.x = 4
    BlockDim.y = 3
    Nb_threads_per_block = BlockDim.x x BlockDim.y = 4 x 3 = 12
    threadIdx.x = 1
    threadIdx.y = 2
    BlockDim.x = 4
    Thread_loc_id = threadIdx.y x BlockDim.x + threadIdx.x = 2 x 4 + 1 = 9
    Thread_glob_id = Block_glob_id x Nb_threads_per_block + Thread_loc_id = 1 x 12 + 9 = 21
```

![Cours 1 图 060](Images/cours1_img_060.jpg)

```text
CUDA programming
GPU
Kernel declaration
    Function attribute: __global__
Compute thread index depending on the grid and blocks
    Example on the right with a 1D grid and 1D blocks
We add a test, checking the index is not greater than the array size
    Correspond to the boundary of the original loop

__global__ void vecAddKernel(
    double *a,
    double *b,
    double *c, int N) {
    int i;
    i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i<N) {
    c[i] = a[i]+b[i];
    }
}
82
```

![Cours 1 图 061](Images/cours1_img_061.jpg)

### Kernels invocation

- How to choose the sizes of the grid and the blocks in the kernel ?
- The user specifies the sizes at kernel invocation
- Several ways to do it

```text
- Most common syntax of kernel invocation on the device
my_kernel<<<Dg, Db>>>(arg1, arg2, arg3);
- Dg: grid size (e.i., number of blocks in each dimension) (type dim3)
- Db: block size (e.i., number of threads in each dimension) (type dim3)
```

```text
Total number of blocks?
```

```text
Thread number per block?
```

- Total number of threads ?

### Kernels invocation

- Blackwell introduced a new level
- Thread block cluster
- Between GRID and BLOCK
- Not possible to integrate that into <<<Dg, Db>>>
- Compatibility issue
-  compile-time kernel attribute
- cluster_dims__(X,Y,Z)
-  or use cudaLaunchKernelEx

### Complete CUDA programm

> 校注：本节对应原 PDF 第 84–93 页逐步展示的 HOST／DEVICE 双栏示例。自动提取混合了两栏与页眉，以下代码仅供查找原页，不能视为可编译的完整程序。

#### HOST

- void vectAdd( double * a, double * b, double * c, int N)
- double 大 adouble double 大c
- cudaMalloc((void **)&d_a, N*sizeof(double)) cudaMalloc((void **)&d_b, N*sizeof(double)); cudaMalloc((void **)&d_c, N*sizeof(double));
- a a, N* sizeof(double),cudaMemcpyHos ecudaMemcpy(d_b, N 大 *sizeof(double),cudaMemcpyHostToDevice)cudaMemCpy(d c, 大 s zeof(double),cudaMemcpyHostToDevice)
- vectAddKernel<<<32,64>>>(d_a, d_b, d_c, N);
- cudaMemcpy(c, d c, N sizeof(double), cudaMemcpyDeviceToHost);
- cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

#### DEVICE

- _global__ void vecAddKernel( double *a, double *b, double *c, int N)
- int i ;
- i = blockIdx.x * blockDim.x + threadIdx.x ;
- if ( i<N ) c[i] = a[i]+b[i];

### Programme CUDA complet

#### HOST

- void vectAdd( double * a, double * b, double * c, int N)
- double * d a double double
- cudaMalloc((void **)&d_a, N*sizeof(double)); cudaMalloc((void **)&d_b, N*sizeof(double)); cudaMalloc((void **)&d_c, N*sizeof(double));
- cudaMemcpy(d_a, a, N*sizeof(double), cudaMemcpyHostToDevice); cudaMemcpy(d_b, b, N*sizeof(double), cudaMemcpyHostToDevice);
- vectAddKernel<<<32,64>>>(d_a, d_b, d_c, N);
- cudaMemcpy(c, d_c, N*sizeof(double), cudaMemcpyDeviceToHost);
- cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

#### DEVICE

```text
__global__ void vecAddKernel( double *a, double *b, double *c, int N) {
    int i;

    i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i<N) {
    c[i] = a[i]+b[i];
    }
}
```

### Programme CUDA complet

#### HOST

- void vectAdd( double * a, double * b, double * c, int N)

```cpp
double * d_a ;
double * d_b ;
double * d_c ;
```

```c
cudaMalloc((void **)&d_a, N*sizeof(double));
cudaMalloc((void **)&d_b, N*sizeof(double));
cudaMalloc((void **)&d_c, N*sizeof(double));
```

```cpp
cudaMemcpy(d_a, a, N*sizeof(double), cudaMemcpyHostToDevice);
cudaMemcpy(d_b, b, N*sizeof(double), cudaMemcpyHostToDevice);
```

```text
vectAddKernel<<<32,64>>>(d_a, d_b, d_c, N);
```

- cudaMemcpy(c, d_c, N*sizeof(double), cudaMemcpyDeviceToHost);

```cpp
cudaFree(d_a);
cudaFree(d_b);
cudaFree(d_c);
```

#### DEVICE

```text
__global__ void vecAddKernel( double *a, double *b, double *c, int N) {
    int i;

    i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i<N) {
    c[i] = a[i]+b[i];
    }
}
```

### Programme CUDA complet

#### HOST

- void vectAdd( double * a, double * b, double * c, int N)
- double * d a double * d b double d c
- cudaMalloc((void **)&d_a, N*sizeof(double)); cudaMalloc((void **)&d_b, N*sizeof(double)); cudaMalloc((void **)&d_c, N*sizeof(double));
- cudaMemcpy(d_a, a, N*sizeof(double), cudaMemcpyHostToDevice); cudaMemcpy(d_b, b, N*sizeof(double), cudaMemcpyHostToDevice);
- vectAddKernel<<<32,64>>>(d_a, d_b, d_c, N);
- cudaMemcpy(c, d_c, N*sizeof(double), cudaMemcpyDeviceToHost);
- cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

#### DEVICE

```text
__global__ void vecAddKernel( double *a, double *b, double *c, int N) {
    int i;

    i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i<N) {
    c[i] = a[i]+b[i];
    }
}
```

### Programme CUDA complet

#### HOST

- void vectAdd( double * a, double * b, double * c, int N)
- double * d a double * d b double d c
- cudaMalloc((void **)&d_a, N*sizeof(double)); cudaMalloc((void **)&d_b, N*sizeof(double)); cudaMalloc((void **)&d_c, N*sizeof(double));
- cudaMemcpy(d_a, a, N*sizeof(double), cudaMemcpyHostToDevice); cudaMemcpy(d_b, b, N*sizeof(double), cudaMemcpyHostToDevice);
- vectAddKernel<<<32,64>>>(d_a, d_b, d N)
- cudaMemcpy(c, d_c, N*sizeof(double), cudaMemcpyDeviceToHost);
- cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

#### DEVICE

- global _ void vecAddKernel( double *a, double *b, double *c, int N)
- int i ;
- i = blockIdx.x * blockDim.x + threadIdx.x ;
- if ( i<N ) { c[i] = a[i]+b[i];

```text
__global__ void vecAddKernel( double *a, double *b, double *c, int N) {
    int i;

    i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i<N) {
    c[i] = a[i]+b[i];
    }
}
```

### Programme CUDA complet

#### HOST

- void vectAdd( double * a, double * b, double * c, int N)
- double * d a double * d b double d c
- cudaMalloc((void **)&d_a, N*sizeof(double)); cudaMalloc((void **)&d_b, N*sizeof(double)); cudaMalloc((void **)&d_c, N*sizeof(double));
- cudaMemcpy(d_a, a, N*sizeof(double), cudaMemcpyHostToDevice); cudaMemcpy(d_b, b, N*sizeof(double), cudaMemcpyHostToDevice);
- vectAddKernel<<<32,64>>>(d_a, d_b, d_c, N);
- cudaMemcpy(c, d_c, N*sizeof(double), cudaMemcpyDeviceToHost);
- cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

#### DEVICE

### Programme CUDA complet

#### HOST

- void vectAdd( double * a, double * b, double * c, int N)

```cpp
double * d_a ;
double * d_b ;
double * d_c ;
```

- cudaMalloc((void **)&d_a, N*sizeof(double)); cudaMalloc((void **)&d_b, N*sizeof(double)); cudaMalloc((void **)&d_c, N*sizeof(double));
- cudaMemcpy(d_a, a, N*sizeof(double), cudaMemcpyHostToDevice); cudaMemcpy(d_b, b, N*sizeof(double), cudaMemcpyHostToDevice);
- vectAddKernel<<<32,64>>>(d_a, d_b, d_c, N);
- cudaMemcpy(c, d_c, N*sizeof(double), cudaMemcpyDeviceToHost);
- cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

#### DEVICE

```text
__global__ void vecAddKernel( double *a, double *b, double *c, int N) {
    int i;

    i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i<N) {
    c[i] = a[i]+b[i];
    }
}
```

### Programme CUDA complet

#### HOST

- void vectAdd( double * a, double * b, double * c, int N)

```cpp
double * d_a ;
double * d_b ;
double * d_c ;
```

- cudaMalloc((void **)&d_a, N*sizeof(double)); cudaMalloc((void **)&d_b, N*sizeof(double)); cudaMalloc((void **)&d_c, N*sizeof(double));
- cudaMemcpy(d_a, a, N*sizeof(double), cudaMemcpyHostToDevice); cudaMemcpy(d_b, b, N*sizeof(double), cudaMemcpyHostToDevice);
- vectAddKernel<<<32,64>>>(d_a, d_b, d_c, N);
- cudaMemcpy(c, d_c, N*sizeof(double), cudaMemcpyDeviceToHost);
- cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

#### DEVICE

```text
__global__ void vecAddKernel( double *a, double *b, double *c, int N) {
    int i;

    i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i<N) {
    c[i] = a[i]+b[i];
    }
}
```

### Programme CUDA complet

#### HOST

- void vectAdd( double * a, double * b, double * c, int N)
- double * d a double * d b double d c

```c
cudaMalloc((void **)&d_a, N*sizeof(double));
cudaMalloc((void **)&d_b, N*sizeof(double));
cudaMalloc((void **)&d_c, N*sizeof(double));
```

- cudaMemcpy(d_a, a, N*sizeof(double), cudaMemcpyHostToDevice); cudaMemcpy(d_b, b, N*sizeof(double), cudaMemcpyHostToDevice);
- vectAddKernel<<<32,64>>>(d_a, d_b, d_c, N);
- cudaMemcpy(c, d_c, N*sizeof(double), cudaMemcpyDeviceToHost);

```cpp
cudaFree(d_a);
cudaFree(d_b);
cudaFree(d_c);
```

#### DEVICE

```text
__global__ void vecAddKernel( double *a, double *b, double *c, int N) {
    int i;

    i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i<N) {
    c[i] = a[i]+b[i];
    }
}
```
