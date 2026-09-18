# Benchmark Reproduction

## Reproducing `results.txt`

The file `results.txt` contains results specifically for the matrix multiplication benchmark (`matmul`) with configured parameters that generate 8 tasks per execution.

To reproduce these results:

1. **Compile the benchmark** (ensure `PREFIX` points to your installation):

    ```bash
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/jianyeshi/Note/AISE/Projet/install_dir/lib
    make matmul PREFIX=/home/jianyeshi/Note/AISE/Projet/install_dir
    ```

2. **Run the commands**:

    ```bash
    echo "--- DYNAMIC ---"
    EXPRESSO_SCHEDULE=dynamic ./matmul 640 640 640 80

    echo "--- STATIC ---"
    EXPRESSO_SCHEDULE=static ./matmul 640 640 640 80

    echo "--- BALANCED ---"
    EXPRESSO_SCHEDULE=balanced ./matmul 640 640 640 80
    ```

## Reproducing `experiment_results.txt`

The file `experiment_results.txt` contains a comprehensive suite of tests across all benchmarks (`dot`, `vecmul`, `matmul`, `list`) with varying thread counts and schedules.

To reproduce the full experiment suite, you can use the following script:

```bash
#!/bin/bash

# Ensure libraries are found
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/jianyeshi/Note/AISE/Projet/install_dir/lib
# Compile all tests
make all PREFIX=/home/jianyeshi/Note/AISE/Projet/install_dir

echo "=== System Info ==="
lscpu | grep "Model name"
lscpu | grep "CPU(s):"
echo ""
echo "=== Experiment started at $(date) ==="
echo ""

echo "========== DOT EXPERIMENTS =========="
for t in 1 2 4 8; do
    echo "--- dot threads=$t ---"
    EXPRESSO_WORKER_COUNT=$t ./dot 10000000 100000
    echo "" # Empty line for readable format like original file
done

echo "========== VECMUL EXPERIMENTS =========="
for t in 1 2 4 8; do
    echo "--- vecmul threads=$t ---"
    EXPRESSO_WORKER_COUNT=$t ./vecmul 10000000 100000
    echo ""
done

echo "========== MATMUL EXPERIMENTS =========="
for s in dynamic static balanced; do
    for t in 1 2 4 8; do
        echo "--- matmul sched=$s threads=$t ---"
        EXPRESSO_SCHEDULE=$s EXPRESSO_WORKER_COUNT=$t ./matmul 640 640 640 80
        echo ""
    done
done

echo "========== LIST EXPERIMENTS =========="
for s in dynamic static balanced; do
    for t in 1 2 4 8; do
        echo "--- list sched=$s threads=$t ---"
        EXPRESSO_SCHEDULE=$s EXPRESSO_WORKER_COUNT=$t ./list 5
        echo ""
    done
done

echo "=== Experiment completed at $(date) ==="
```
