#!/usr/bin/env python3

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys
import os

args = sys.argv
if len(args) != 3:
    print("Usage: ./script/plot_luminosity.py <output_folder> <dataset_name>")
    sys.exit(1)

output_folder = args[1]
os.makedirs(output_folder, exist_ok=True)

star = args[2]

data_path = f"data/{star}_light_curve.csv"

try:
    data = pd.read_csv(data_path)
    print(f"Loading data from {data_path}")
except FileNotFoundError:
    print(f"Error: File {data_path} not found")
    sys.exit(1)

time = data.iloc[:, 0]
flux = data.iloc[:, 1]
time_min = time.min()
time_max = time.max()
flux_min = flux.min()
flux_max = flux.max()

plt.figure(figsize=(18, 6))
plt.plot(time, flux, 'steelblue', linewidth=0.7)
plt.xlabel('Time [days]')
plt.ylabel('Normalized Flux')
plt.title(f'{star} Light Curve')
plt.xlim(time_min, time_max)
plt.ylim(flux_min, flux_max)

plt.xticks(np.linspace(time_min, time_max, 10))
plt.yticks(np.linspace(flux_min, flux_max, 10))

output_path = f"{output_folder}/luminosity_{star}.png"
plt.savefig(output_path, dpi=300, bbox_inches='tight')
plt.close()

print(f"Plot saved to {output_path}")