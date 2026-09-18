# Lab 7 – MNIST Inference Engine (C)

## Overview

This project implements a pure‑C inference engine tailored to the fully connected MNIST classifiers shipped with the lab (exported as ONNX graphs).  
Key components:
- Reuse the optimized SGEMM kernels from Lab 6 for the `Gemm` operator.
- Implement the remaining ONNX operators needed by the models (`Flatten`, `Add`, `Relu`) and schedule them in topological order.
- Cover every operator plus the scheduler with Unity unit tests and verify accuracy on the 100 images from `image-test-set/`.
- Provide a CLI tool (`infer`) and benchmarking utilities to measure latency, accuracy, and optional energy counters.

## Requirements

Developed and tested on Fedora; equivalent packages exist on other distributions:

- C compiler (GCC 11+ recommended)
- CMake ≥ 3.15
- Protobuf & Protobuf-C  
  `sudo dnf install protobuf-compiler protobuf-devel protobuf-c protobuf-c-devel` (Fedora)  
  `sudo apt install protobuf-compiler libprotobuf-dev libprotobuf-c-dev` (Debian/Ubuntu)
- OpenBLAS (optional, required only for the BLAS SGEMM backend)  
  `sudo dnf install openblas openblas-devel` / `sudo apt install libopenblas-dev`
- Python 3 (for profiling chart generation)

After cloning, initialize submodules if the template did not do it automatically:

```bash
git submodule update --init --recursive
```

## Build & Test

```bash
cmake -S . -B build
cmake --build build
cmake --build build --target test
```

`test_runner` executes eight Unity tests covering the ONNX parser, each operator, full inference for one sample, and dataset accuracy (≈98 % on the provided 100 images). Required fixtures are copied into the build tree automatically.

## CLI Usage

The `infer` executable lives in `build/`. Basic invocation:

```bash
./build/infer models/mnist.onnx image-test-set/image_0.ubyte image-test-set/labels.csv
```

Example output:

```
Predicted digit: 7 (probability 10.0955)
Expected label: 7 -> OK
```

- The label CSV argument is optional; when provided the CLI prints the expected label and checks the prediction.
- Images follow the `image_<index>.ubyte` naming convention inside `image-test-set/`.

### Runtime options

```
--profile            # print per-operator timings and emit PROFILE_JSON
--gemm=<backend>     # choose SGEMM backend: naive, ikj (default), blocked, omp, blas
```

Exemple :
```bash
./build/infer --profile --gemm=omp model.onnx image.ubyte [labels.csv]
```

Unsupported options yield an error and the usage string.

## Benchmarking & Profiling

`performance/benchmark.sh` walks through every ONNX model, runs inference on all 100 images, and records accuracy, average latency, and optional energy statistics into `performance/results.json`.

```bash
# Example: bind inference to cores 0-7, use the OpenMP SGEMM backend (16 threads)
USE_SUDO=1 CPU_SET=0-7 GEMM_BACKEND=omp PROFILE_INFERENCE=1 \
    performance/benchmark.sh ./build/infer models image-test-set image-test-set/labels.csv 1

cat performance/results.json
```

```bash
USE_SUDO=1 performance/benchmark.sh # enable le energie test 
```

`PROFILE_INFERENCE=1` (default) appends `--profile` to each run so that the script collects the emitted `PROFILE_JSON` lines and aggregates them. Use `performance/profile_charts.py` to convert the JSON results into plots showing per-operator time vs. call count:

```bash
python3 performance/profile_charts.py \
    --input performance/results.json \
    --output performance/charts
```

## Repository Layout

```
.
├── src/               # Inference engine, CLI helpers, ONNX parser glue
├── tests/             # Unity test suite
├── external/          # SGEMM kernels and ONNX protobuf bindings
├── models/            # Provided ONNX models
├── image-test-set/    # MNIST samples + labels
├── performance/       # Benchmark scripts, JSON results, profiling charts
└── projectLatex/      # LaTeX report material
```

## LaTeX Report

- `wc -w projectLatex/report.tex` approximates the current word count of the report from the repository root.
- `cd projectLatex && pdflatex report.tex` builds `projectLatex/report.pdf`; install TeX Live (or an equivalent LaTeX distribution) beforehand.
