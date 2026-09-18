#!/usr/bin/env python3

import pandas as pd
import numpy as np
from tqdm import tqdm
import matplotlib as mpl
mpl.use("Agg")  # Use a non-interactive backend for matplotlib

import matplotlib.pyplot as plt
import seaborn as sns
import subprocess
import logging

from rich.console import Console
from rich.logging import RichHandler
from rich.table import Table
from pathlib import Path

console = Console()

# Repeat the same MC estimation 2048 times
# Plot a distribution of the generated Pi values
# As well as the execution time distribution
# The goal here is to have the students check:
# - The distribution of the Pi values (Should be normal around 3.14 if their code is correct and a good random generator is used)
# - The execution time distribution (Should be normal around the mean execution time if their machine is stable)
def run_stability(kernel, output):
    """Runs the Pi Estimation 2048 times and plot the estimation and execution time distributions."""
    logger.info("Running stability analysis (This may take a while)...")

    nsamples = 5_000_000

    subprocess.check_output(
        [str(kernel.resolve()), str(nsamples), "2048", output / "stability.csv"]
    )
    if not (output / "stability.csv").exists():
        raise FileNotFoundError(
            f"Stability file {output / 'stability.csv'} does not exist ! Did you implement CSV output ?"
        )

    raw_data = pd.read_csv(output / "stability.csv")
    fig, axs = plt.subplots(2, 1, figsize=(12, 12), layout="constrained")

    # First plot the distribution of Pi values
    ax = axs[0]
    sns.kdeplot(
        data=raw_data,
        x="Pi",
        ax=ax,
        fill=True,
        cmap="magma",
        cut=0,
        label="Pi Estimations",
    )
    ax.set_title(
        f"Distributions of Pi Estimations ({len(raw_data)} samples)",
        fontweight="bold",
        fontsize=16,
    )
    ax.set_xlabel("Pi Value")
    ax.set_ylabel("Density", labelpad=10)
    ax.axvline(
        raw_data["Pi"].mean(),
        color="blue",
        linestyle="--",
        label=f"Mean Pi: {raw_data['Pi'].mean():.5f}",
    )
    ax.axvline(
        np.pi,
        color="red",
        linestyle="--",
        label="True Pi Value",
    )
    ax.legend(loc="upper right", fontsize=10)

    # Now plot the distribution of execution time
    ax = axs[1]
    sns.histplot(
        data=raw_data,
        x="Time",
        ax=ax,
        bins=128,
        label="Execution Time",
    )
    ax.set_title(
        f"Distributions of Execution Time ({len(raw_data)} samples)",
        fontweight="bold",
        fontsize=16,
    )
    ax.set_xlabel("Execution Time")
    # We limit ourself to the 1% and 99% quantile of the data
    # to avoid outliers that could skew the plot
    _, vmax = np.quantile(raw_data["Time"], [0.01, 0.99])
    ax.set_xlim(raw_data["Time"].min(), vmax)
    ax.set_xticks(np.linspace(raw_data["Time"].min(), vmax, 10))

    ax.set_ylabel("Density", labelpad=10)

    ax.axvline(
        raw_data["Time"].mean(),
        color="blue",
        linestyle="--",
        label=f"Mean Time: {raw_data['Time'].mean():.5f}",
    )
    ax.legend(loc="upper left", fontsize=10)

    fig.savefig(output / "stability.png", dpi=200)
    plt.close(fig)

    logger.info(f"Stability analysis completed, results in {output / 'stability.png'}")

# Repeat the same MC estimation with an increasing number of samples
# So the student can see the convergence of the Pi value and the execution time
# The goal here is to have the students check:
# - The convergence of the Pi value (Should converge to 3.14 in the overworld) after >10e6 samples
# - The execution time should scale linearly with the number of samples
def run_convergence(kernel, output):
    """Runs the Pi Estimation with different number of samples and plot the convergence."""

    logger.info("Running convergence experiment (this may take a while)")

    min_iter = 1_000
    max_iter = 1_000_000
    # We use a geometric progression to cover a large range of values
    # and to avoid too many iterations
    iters = np.geomspace(min_iter, max_iter, 256, dtype=int)
    pi_values = []

    for i in tqdm(iters, desc="Running convergence analysis", unit="iteration"):
        subprocess.check_output(
            [str(kernel.resolve()), str(int(i)), "100", output / "tmp.csv"]
        )
        data = pd.read_csv(output / "tmp.csv")
        data["error"] = np.abs(data["Pi"] - np.pi) / np.pi
        (output / "tmp.csv").unlink()
        pi_values.append(
            (
                i,
                data["error"].mean(),
                data["error"].std(),
                data["Pi"].mean(),
                data["Pi"].std(),
                data["Time"].mean(),
                data["Time"].std(),
            )
        )

    pi_values = pd.DataFrame(
        pi_values,
        columns=[
            "Iteration",
            "Residual",
            "std_residual",
            "Pi",
            "std_pi",
            "Time",
            "std_time",
        ],
    )
    pi_values.to_csv(output / "convergence.csv", index=False)

    fig, axs = plt.subplots(2, 1, figsize=(12, 6), layout="constrained")

    ax = axs[0]
    # Plot lineplot with confidence interval
    sns.lineplot(
        data=pi_values, x="Iteration", y="Residual", ax=ax, label="Mean Relative Error"
    )

    n = 100  # number of Monte Carlo runs per iteration
    stderr = pi_values["std_residual"] / np.sqrt(n)
    upper = pi_values["Residual"] + 1.96 * stderr
    lower = pi_values["Residual"] - 1.96 * stderr

    ax.fill_between(
        pi_values["Iteration"], lower, upper, alpha=0.3, label="95% Confidence Interval"
    )

    ax.set_title(
        "Evolution of Pi Relative Error\ndepending on the number of Monte-Carlo samples",
        fontweight="bold",
        fontsize=11,
    )
    ax.set_xlabel("Number of Monte-Carlo Samples")
    ax.set_xlim(pi_values["Iteration"].min(), pi_values["Iteration"].max())
    ax.set_xscale("log")

    from matplotlib.ticker import FuncFormatter
    def percent(x, pos):
        return f"{x * 100:.2f}%"

    ax.set_ylabel("Relative Error %")
    ax.yaxis.set_major_formatter(FuncFormatter(percent))
    ax.grid("y")

    ax.legend(loc="upper center", bbox_to_anchor=(0.5, -0.22), ncol=3, fontsize=10)

    ax = axs[1]

    sns.lineplot(data=pi_values, x="Iteration", y="Time", ax=ax, label="Execution Time")
    n = 100  # number of Monte Carlo runs per iteration
    stderr = pi_values["std_time"] / np.sqrt(n)
    upper = pi_values["Time"] + 1.96 * stderr
    lower = pi_values["Time"] - 1.96 * stderr
    ax.fill_between(
        pi_values["Iteration"], lower, upper, alpha=0.3, label="95% Confidence Interval"
    )

    ax.set_title(
        "Evolution of execution time\ndepending on the number of Monte-Carlo samples",
        fontweight="bold",
        fontsize=11,
    )
    ax.set_xlabel("Number of Monte-Carlo Samples")
    ax.set_xlim(pi_values["Iteration"].min(), pi_values["Iteration"].max())
    ax.set_ylabel("Execution Time (s)")
    ax.legend(loc="upper center", bbox_to_anchor=(0.5, -0.22), ncol=3, fontsize=10)
    ax.grid("y")

    fig.savefig(output / "convergence.png", dpi=200)
    plt.close(fig)

    logger.info(f"Convergence analysis completed, results in {output / 'convergence.png'}")


def main(args):

    import time

    table = Table(
        title="Pi Estimator Analysis", show_header=True, header_style="bold magenta"
    )
    table.add_column("Experiments", justify="left", style="cyan")
    table.add_column("Description", justify="left", style="magenta")
    table.add_column("Run Time", justify="left", style="green")

    experiments = {"Stability": run_stability, "Convergence": run_convergence}
    logging.info("Starting experiments...")
    for name, func in experiments.items():
        begin = time.time()
        func(args.kernel, args.output)
        end = time.time()
        elapsed = end - begin
        table.add_row(
            name,
            f"{func.__doc__}",
            f"{elapsed:.2f} seconds",
        )
    console.print(table)

    logging.info("Experiments completed.")


def setup_logging():
    """Setup logging configuration."""
    logging.basicConfig(
        level=logging.DEBUG,
        format="%(message)s",
        datefmt="[%X]",
        handlers=[RichHandler(console=console)],
    )
    logging.getLogger("matplotlib").setLevel(logging.WARNING)
    global logger
    logger = logging.getLogger("rich")
    logger.info("Logging setup complete.")
    return logger


def parse_args():
    import argparse

    parser = argparse.ArgumentParser(description="Analyse data.")
    parser.add_argument(
        "--kernel",
        type=Path,
        help="Path to the piestimator kernel",
        default="./piestimator",
    )
    parser.add_argument("output", type=Path, help="Output directory")

    args = parser.parse_args()

    if not args.kernel.exists():
        raise FileNotFoundError(
            f"Kernel file {args.kernel} does not exist ! Are you sure you ran make ?"
        )
    if not args.output.exists():
        args.output.mkdir(parents=True, exist_ok=True)

    return args


if __name__ == "__main__":
    args = parse_args()
    setup_logging()
    main(args)
