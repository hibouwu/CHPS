#!/usr/bin/env python3
import psutil
import time
import pandas as pd
import numpy as np
import matplotlib as mpl
mpl.use("Agg")
import matplotlib.pyplot as plt
import seaborn as sns
import tqdm
import subprocess
import os
from scipy import stats

# ----------------------------------- DO NOT MODIFY BELOW THIS LINE ----------------------------------- #

def measure_idle_system():
    run_time = 5 * 60 # seconds
    start_time = time.time()

    data = []
    print(f"Monitoring system usage for {run_time} seconds...")
    print("(Do not interrupt this process)")
    while time.time() - start_time < run_time:
        cpu_usage = psutil.cpu_percent(interval=1)
        mem = psutil.virtual_memory()
        mem_usage = mem.percent
        data.append((time.time() - start_time, cpu_usage, mem_usage))

        time.sleep(0.5)

    df = pd.DataFrame(data, columns=["Time (s)", "CPU Usage (%)", "Memory Usage (%)"])
    df.to_csv("results/system_usage.csv", index=False)

    fig, axs = plt.subplots(2, 1, figsize=(6, 4))
    ax = axs[0]
    sns.lineplot(x="Time (s)", y="CPU Usage (%)", data=df,
                    ax=ax)
    ax.set_title("CPU Usage Over Time")
    plt.xlabel("Time (s)")
    ax.margins(0)
    ax.grid("y")
    ax.set_xticks(np.linspace(0, run_time, 11))
    # We set vmin/vmax to the closest 10% up and down
    vmin = int(df["CPU Usage (%)"].min() // 10 * 10)
    vmax = int((df["CPU Usage (%)"].max() // 10 + 1) * 10)
    ax.set_yticks(np.linspace(vmin, vmax, 11))

    ax = axs[1]
    sns.lineplot(x="Time (s)", y="Memory Usage (%)", data=df,
                    ax=ax)
    ax.set_title("Memory Usage Over Time")
    plt.xlabel("Time (s)")
    ax.margins(0)
    ax.grid("y")
    ax.set_xticks(np.linspace(0, run_time, 11))
    ax.set_yticks(np.linspace(0, 100, 11))

    fig.tight_layout()
    fig.savefig("results/system_usage.png", dpi=300, bbox_inches="tight")
    plt.close()

# ----------------------------------- DO NOT MODIFY ABOVE THIS LINE ----------------------------------- #

def measure_bls_stability():
    print("Loading Kepler-8 dataset...")
    df = pd.read_csv("data/kepler-8_light_curve.csv")
    
    # Subsample the dataset to ~2000 points randomly
    n_samples = min(2000, len(df))
    df_subsampled = df.sample(n=n_samples, random_state=42)
    
    # Sort by time after subsampling (very important!)
    df_subsampled = df_subsampled.sort_values(by="time")
    
    # Save the subsampled dataset (note: run_bls.py adds _light_curve.csv automatically)
    df_subsampled.to_csv("data/kepler-8_subsampled_light_curve.csv", index=False)
    
    print(f"Subsampled dataset from {len(df)} to {len(df_subsampled)} points")
    
    # Measure BLS execution time multiple times
    n_runs = 100
    execution_times = []
    
    print(f"Running BLS algorithm {n_runs} times to measure stability...")
    
    for i in tqdm.tqdm(range(n_runs), desc="BLS runs"):
        start_time = time.time()
        
        # Run the BLS script using subprocess
        try:
            result = subprocess.run([
                "/home/jianyeshi/Note/glhpc/glhpc-lab-5-hibouwu/venv/bin/python", 
                "scripts/run_bls.py", 
                "kepler-8_subsampled"
            ], 
            capture_output=True, 
            text=True, 
            check=True)
            
            end_time = time.time()
            execution_time = end_time - start_time
            execution_times.append(execution_time)
            
        except subprocess.CalledProcessError as e:
            print(f"Error in run {i}: {e}")
            continue
    
    # Save raw data
    stability_df = pd.DataFrame({
        'run_number': range(1, len(execution_times) + 1),
        'execution_time': execution_times
    })
    stability_df.to_csv("results/stability_bls.csv", index=False)
    
    # Generate distribution plots in the style of the provided image
    fig = plt.figure(figsize=(12, 8))
    
    # Set overall title with statistics
    mean_time = np.mean(execution_times)
    cv = (np.std(execution_times) / mean_time) * 100
    fig.suptitle(f'BLS Execution Time Stability on Kepler-8 Subsampled Dataset\nMean: {mean_time:.2f} s, CoV: {cv:.2f}%', 
                 fontsize=14, fontweight='bold')
    
    # Boxplot (top left) - HORIZONTAL
    ax1 = plt.subplot(2, 2, 1)
    bp = sns.boxplot(x=execution_times, ax=ax1, color='plum', width=0.6)
    ax1.set_title('Boxplot', fontweight='bold')
    ax1.set_ylabel('')
    ax1.set_xlabel('Time (s)')
    ax1.grid(True, alpha=0.3)
    
    # Histogram (top right)
    ax2 = plt.subplot(2, 2, 2)
    ax2.hist(execution_times, bins=20, alpha=0.8, color='plum', edgecolor='black', linewidth=0.5)
    # Add KDE overlay
    kde = stats.gaussian_kde(execution_times)
    x_range = np.linspace(min(execution_times), max(execution_times), 200)
    kde_values = kde(x_range)
    # Scale KDE to match histogram
    ax2_twin = ax2.twinx()
    ax2_twin.plot(x_range, kde_values, color='purple', linewidth=2)
    ax2_twin.set_ylabel('')
    ax2_twin.set_yticks([])
    ax2.set_title('Histogram', fontweight='bold')
    ax2.set_xlabel('Time (s)')
    ax2.set_ylabel('Count')
    ax2.grid(True, alpha=0.3)
    
    # KDE plot (bottom left)
    ax3 = plt.subplot(2, 2, 3)
    sns.kdeplot(execution_times, ax=ax3, fill=True, color='plum', alpha=0.8)
    ax3.set_title('KDE plot', fontweight='bold')
    ax3.set_xlabel('Time (s)')
    ax3.set_ylabel('Density')
    ax3.grid(True, alpha=0.3)
    
    # Violin plot (bottom right) - HORIZONTAL
    ax4 = plt.subplot(2, 2, 4)
    parts = ax4.violinplot([execution_times], positions=[1], widths=0.8, showmeans=False, 
                          showmedians=True, showextrema=True, vert=False)
    # Style the violin plot to match the image
    for pc in parts['bodies']:
        pc.set_facecolor('purple')
        pc.set_alpha(0.8)
    parts['cmedians'].set_color('white')
    parts['cmedians'].set_linewidth(2)
    parts['cbars'].set_color('black')
    parts['cmins'].set_color('black')
    parts['cmaxes'].set_color('black')
    
    ax4.set_title('Violin Plot', fontweight='bold')
    ax4.set_xlabel('Time (s)')
    ax4.set_ylabel('')
    ax4.set_yticks([1])
    ax4.set_yticklabels([''])
    ax4.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.subplots_adjust(top=0.9)  # Make room for suptitle
    plt.savefig("results/stability_bls.png", dpi=300, bbox_inches="tight")
    plt.close()
    
    # Print statistics
    mean_time = np.mean(execution_times)
    std_time = np.std(execution_times)
    cv = (std_time / mean_time) * 100  # Coefficient of variation
    
    print(f"\nBLS Stability Results:")
    print(f"Number of successful runs: {len(execution_times)}")
    print(f"Mean execution time: {mean_time:.4f} seconds")
    print(f"Standard deviation: {std_time:.4f} seconds")
    print(f"Coefficient of variation: {cv:.2f}%")
    print(f"Min time: {np.min(execution_times):.4f} seconds")
    print(f"Max time: {np.max(execution_times):.4f} seconds")
    
    # Finally, clean up the subsampled dataset
    os.remove("data/kepler-8_subsampled_light_curve.csv")


def main():
    os.makedirs("results", exist_ok=True)
    measure_bls_stability()
    measure_idle_system()



if __name__ == "__main__":
    with mpl.rc_context({'font.size': 7}):
        main()