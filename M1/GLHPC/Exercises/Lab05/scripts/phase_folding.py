#!/usr/bin/env python3

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys
from scipy import stats
import os

args = sys.argv
if len(args) != 4:
    print("Usage: ./scripts/phase_folding.py <output_folder> <dataset_name> <period>")
    sys.exit(1)

output_folder = args[1]
os.makedirs(output_folder, exist_ok=True)

star = args[2]
period = float(args[3])

data_path = f"data/{star}_light_curve.csv"

try:
    data = pd.read_csv(data_path)
    print(f"Loading data from {data_path}")
except FileNotFoundError:
    print(f"Error: File {data_path} not found")
    sys.exit(1)
if 'time' in data.columns and 'flux' in data.columns:
    time = data['time']
    flux = data['flux']
else:
    time = data.iloc[:, 0]
    flux = data.iloc[:, 1]

phase = (time % period) / period
phase = phase - 0.5

# Sort by phase
sort_idx = np.argsort(phase)
phase_sorted = phase.iloc[sort_idx] if hasattr(phase, 'iloc') else phase[sort_idx]
flux_sorted = flux.iloc[sort_idx] if hasattr(flux, 'iloc') else flux[sort_idx]

# Double plotting to improve visualization
phase = np.concatenate([phase_sorted, phase_sorted + 1])
flux = np.concatenate([flux_sorted, flux_sorted])

# Create the plot
plt.figure(figsize=(18, 6))
plt.plot(phase, flux, 'steelblue', linewidth=0.7, label='Phase-folded data')

# Add binned mean
bins = 200
bin_means, bin_edges, _ = stats.binned_statistic(phase, flux, statistic='mean', bins=bins)
bin_centers = (bin_edges[:-1] + bin_edges[1:]) / 2
plt.plot(bin_centers, bin_means, color="red", linewidth=2, label='Binned mean')

plt.xlabel('Phase')
plt.ylabel('Normalized Flux')
plt.title(f'Phase-Folded {star} Light Curve ({period:.3f} days)')

plt.legend()
plt.xlim(-0.5, 1.5)

plt.xticks(np.linspace(-0.500, 1.500, 10))
plt.yticks(np.linspace(flux.min(), flux.max(), 10))

# Save the plot
output_path = f"{output_folder}/phase_folding_{star}.png"
plt.savefig(output_path, dpi=300, bbox_inches='tight')
plt.close()

print(f"Phase-folded plot saved to {output_path}")
