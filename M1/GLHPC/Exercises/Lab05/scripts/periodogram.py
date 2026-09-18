#!/usr/bin/env python3
import numpy as np
import pandas as pd
import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../libbls/install')))
import bls
import matplotlib.pyplot as plt
import seaborn as sns
from scipy import stats
import json

# List of all Kepler datasets to process
datasets = ["kepler-8", "kepler-17", "kepler-45", "kepler-785"]

# Dictionary to store the results for each dataset
results = {}
true_periods = {}

# Process all datasets
for star in datasets:
    print(f"Processing {star}...")
    
    # Load the dataset
    data = pd.read_csv(f"data/{star}_light_curve.csv")
    
    # Run the BLS algorithm with full periodogram output
    out = bls.bls_periodogram(data["time"].values.astype(np.float64), data["flux"].values.astype(np.float64),
        1.0, 4, 250, 0.02, 0.15, 100)
    
    power = out[:, 0]
    periods = out[:, 1]
    
    # Store the results in the dictionary
    results[star] = pd.DataFrame({"Period (days)": periods, "Power": power})
    
    # Load known planets data
    with open(f"data/{star}_known_planets.json") as f:
        known_planets = json.load(f)
        # Use koi_period as the correct key name
        true_periods[star] = [p["koi_period"] for p in known_planets]

# Create subplots (2x2 grid)
ncols = 2
nrows = 2
fig, axs = plt.subplots(nrows, ncols, figsize=(15, 12))
axs = axs.flatten()

for i, (name, df) in enumerate(results.items()):
    ax = axs[i]
    known_periods = true_periods.get(name, [])
    
    # Plot the periodogram
    ax.plot(df["Period (days)"], df["Power"], 'b-', linewidth=1, alpha=0.7)
    ax.set_xlabel('Period (days)')
    ax.set_ylabel('BLS Power')
    ax.set_title(f'{name.upper()} BLS Periodogram')
    ax.grid(True, alpha=0.3)
    
    # Find and mark the peak
    max_idx = df["Power"].idxmax()
    best_period = df.loc[max_idx, "Period (days)"]
    best_power = df.loc[max_idx, "Power"]
    ax.plot(best_period, best_power, 'ro', markersize=8, 
            label=f'Detected: P={best_period:.3f} d')
    
    # Add vertical lines for known planets
    for j, period in enumerate(known_periods):
        ax.axvline(x=period, color='green', linestyle='--', linewidth=2, alpha=0.8,
                  label=f'Known: P={period:.3f} d')
    
    ax.legend()

plt.tight_layout()

# Save the figure
os.makedirs("./results", exist_ok=True)
plt.savefig("./results/all_periodograms.png", dpi=300, bbox_inches='tight')
print("Periodograms saved as results/all_periodograms.png")