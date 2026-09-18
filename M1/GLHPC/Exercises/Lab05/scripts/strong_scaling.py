#!/usr/bin/env python3

import pandas as pd
import numpy as np
import matplotlib as mpl
# Use matplotlib in non-interactive mode
mpl.use("Agg")
import matplotlib.pyplot as plt
import seaborn as sns
import subprocess
import sys
import os
import time
import psutil

# ----------------------------------- DO NOT MODIFY BELOW THIS LINE ----------------------------------- #
def run_bls(nthreads: int, dataset: str) -> float:

    env = os.environ.copy()
    env["OMP_NUM_THREADS"] = str(nthreads)
    cmd = ["./scripts/run_bls.py", dataset]

    begin = time.time()
    result = subprocess.run(cmd, capture_output=True, text=True, env=env)
    end = time.time()

    elapsed = end - begin
    if result.returncode != 0:
        print(f"Error running BLS with {nthreads} threads on {dataset}:")
        print(result.stderr)
        return None
    
    return elapsed
# ----------------------------------- DO NOT MODIFY ABOVE THIS LINE ----------------------------------- #

def main():
    # Strong scaling test: fixed workload, varying number of threads
    
    # Get current timestamp for results directory
    date = time.strftime("%Y_%m_%d-%H_%M_%S")
    results_dir = f"results/{date}/"
    os.makedirs(results_dir, exist_ok=True)
    
    # Determine maximum number of threads (CPU cores)
    max_threads = psutil.cpu_count(logical=True)
    print(f"System has {max_threads} logical cores")
    
    # Test with different thread counts: 1, 2, 4, 8, 16, ... up to max_threads
    thread_counts = []
    current = 1
    while current <= max_threads:
        thread_counts.append(current)
        current *= 2
    
    # Also add max_threads if it's not already included
    if max_threads not in thread_counts:
        thread_counts.append(max_threads)
    
    thread_counts.sort()
    print(f"Testing with thread counts: {thread_counts}")
    
    # Store results
    execution_times = []
    speedups = []
    efficiencies = []
    
    # Run BLS with different thread counts
    baseline_time = None
    
    for nthreads in thread_counts:
        print(f"Running BLS with {nthreads} threads on kepler-8 dataset...")
        
        # Run multiple times for better accuracy  
        times = []
        for i in range(1):  # 1 run per thread count for faster testing
            elapsed = run_bls(nthreads, "kepler-8")
            if elapsed is not None:
                times.append(elapsed)
                print(f"  Run {i+1}: {elapsed:.2f}s")
        
        if times:
            avg_time = np.mean(times)
            execution_times.append(avg_time)
            
            # Calculate speedup and efficiency
            if baseline_time is None:
                baseline_time = avg_time
                speedup = 1.0
                efficiency = 1.0
            else:
                speedup = baseline_time / avg_time
                efficiency = speedup / nthreads
            
            speedups.append(speedup)
            efficiencies.append(efficiency)
            
            print(f"  Average time: {avg_time:.2f}s, Speedup: {speedup:.2f}x, Efficiency: {efficiency:.2f}")
        else:
            print(f"  Failed to run with {nthreads} threads")
            # Remove this thread count from the list
            thread_counts.remove(nthreads)
    
    # Create results DataFrame
    results_df = pd.DataFrame({
        'threads': thread_counts,
        'execution_time': execution_times,
        'speedup': speedups,
        'efficiency': efficiencies
    })
    
    # Save raw data
    results_df.to_csv(f"{results_dir}strong_scaling_data.csv", index=False)
    print(f"Results saved to {results_dir}strong_scaling_data.csv")
    
    # Create strong scaling plots
    fig, axes = plt.subplots(2, 2, figsize=(12, 10))
    fig.suptitle('BLS Strong Scaling Analysis', fontsize=16, fontweight='bold')
    
    # Plot 1: Execution Time vs Threads
    axes[0, 0].plot(thread_counts, execution_times, 'o-', linewidth=2, markersize=8, color='blue')
    axes[0, 0].set_xlabel('Number of Threads')
    axes[0, 0].set_ylabel('Execution Time (s)')
    axes[0, 0].set_title('Execution Time vs Threads')
    axes[0, 0].grid(True, alpha=0.3)
    axes[0, 0].set_xscale('log', base=2)
    
    # Plot 2: Speedup vs Threads
    axes[0, 1].plot(thread_counts, speedups, 'o-', linewidth=2, markersize=8, color='green', label='Actual')
    # Add ideal speedup line
    axes[0, 1].plot(thread_counts, thread_counts, '--', linewidth=2, color='red', alpha=0.7, label='Ideal')
    axes[0, 1].set_xlabel('Number of Threads')
    axes[0, 1].set_ylabel('Speedup')
    axes[0, 1].set_title('Speedup vs Threads')
    axes[0, 1].grid(True, alpha=0.3)
    axes[0, 1].set_xscale('log', base=2)
    axes[0, 1].legend()
    
    # Plot 3: Efficiency vs Threads
    axes[1, 0].plot(thread_counts, efficiencies, 'o-', linewidth=2, markersize=8, color='orange')
    axes[1, 0].axhline(y=1.0, color='red', linestyle='--', alpha=0.7, label='Perfect Efficiency')
    axes[1, 0].set_xlabel('Number of Threads')
    axes[1, 0].set_ylabel('Efficiency')
    axes[1, 0].set_title('Parallel Efficiency vs Threads')
    axes[1, 0].grid(True, alpha=0.3)
    axes[1, 0].set_xscale('log', base=2)
    axes[1, 0].set_ylim(0, 1.1)
    axes[1, 0].legend()
    
    # Plot 4: Summary table
    axes[1, 1].axis('off')
    table_data = []
    for i, nthreads in enumerate(thread_counts):
        table_data.append([
            f"{nthreads}",
            f"{execution_times[i]:.2f}s",
            f"{speedups[i]:.2f}x",
            f"{efficiencies[i]:.2f}"
        ])
    
    table = axes[1, 1].table(cellText=table_data,
                            colLabels=['Threads', 'Time', 'Speedup', 'Efficiency'],
                            cellLoc='center',
                            loc='center')
    table.auto_set_font_size(False)
    table.set_fontsize(9)
    table.scale(1.2, 1.5)
    axes[1, 1].set_title('Performance Summary', fontweight='bold')
    
    plt.tight_layout()
    plt.savefig(f"{results_dir}strong_scaling.png", dpi=300, bbox_inches="tight")
    plt.close()
    
    print(f"Strong scaling plot saved to {results_dir}strong_scaling.png")
    
    # Print summary
    print("\n=== Strong Scaling Summary ===")
    print(f"Baseline (1 thread): {baseline_time:.2f}s")
    print(f"Best speedup: {max(speedups):.2f}x with {thread_counts[speedups.index(max(speedups))]} threads")
    print(f"Efficiency at max threads: {efficiencies[-1]:.2f}")


if __name__ == "__main__":
    with mpl.rc_context({'font.size': 7}):
        main()