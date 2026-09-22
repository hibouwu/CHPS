#!/usr/bin/env python3
import os
import sys
import numpy as np
import pandas as pd
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../libbls/install')))
import bls
import matplotlib.pyplot as plt
import seaborn as sns
from scipy import stats

args = sys.argv
if len(args) != 2:
    print("Usage: ./script/run_bls.py <dataset_name>")
    sys.exit(1)

data = pd.read_csv(f"./data/{args[1]}_light_curve.csv")

match = bls.bls(
    data["time"].values.astype(np.float64),
    data["flux"].values.astype(np.float64),
    1.0, 4, 250, 0.02, 0.15, 100)

print(match)