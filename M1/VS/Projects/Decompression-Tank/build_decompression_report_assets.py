from pathlib import Path
import json
import math
import os
import subprocess

import matplotlib.pyplot as plt
import pandas as pd
from PIL import Image, ImageOps, ImageDraw


ROOT = Path(__file__).resolve().parent
ASSET_DIR = ROOT / "report_assets"
FIG_DIR = ASSET_DIR / "figures"
DATA_DIR = ASSET_DIR / "data"
LEFT_FRAMES_DIR = ASSET_DIR / "frames_left"
CHART_FRAMES_DIR = ASSET_DIR / "frames_chart"
COMBINED_FRAMES_DIR = ASSET_DIR / "frames_combined"

for path in (CHART_FRAMES_DIR, COMBINED_FRAMES_DIR):
    path.mkdir(parents=True, exist_ok=True)

os.environ.setdefault("MPLCONFIGDIR", "/tmp/mplconfig")  # 改这里：避免 matplotlib 往系统目录写缓存


def load_time_map():
    # 读取 ParaView 导出脚本写出的时间轴信息。
    with (DATA_DIR / "time_map.json").open("r", encoding="utf-8") as fh:
        payload = json.load(fh)
    return payload["labels"], payload["time_values"], payload["focus_times"]


def pick_column(df: pd.DataFrame, candidates):
    for candidate in candidates:
        if candidate in df.columns:
            return candidate
    raise KeyError(f"None of {candidates} found in columns {list(df.columns)}")


def normalise_line_csv(path: Path) -> pd.DataFrame:
    # ParaView 导出的 CSV 列名有时会变，这里统一整理一次。
    df = pd.read_csv(path)
    x_col = pick_column(df, ["Points:0", "Points_X", "arc_length"])
    p_col = pick_column(df, ["p", "p (Point Data)", "p (Points)"])
    out = pd.DataFrame({"x": df[x_col], "p": df[p_col]})
    return out.sort_values("x")


def normalise_time_csv(path: Path) -> pd.DataFrame:
    df = pd.read_csv(path)
    t_col = pick_column(df, ["Time", "time", "TimeValue"])
    p_col = pick_column(df, ["avg(p)", "p", "p (Point Data)", "p (Points)"])
    return pd.DataFrame({"time": df[t_col], "p": df[p_col]})


def build_line_plot():
    # Figure 4：三个代表时刻的轴线压力分布图。
    colors = {"early": "#1f77b4", "mid": "#ff7f0e", "late": "#2ca02c"}
    labels_fr = {
        "early": "Instant precoce",
        "mid": "Instant intermediaire",
        "late": "Instant tardif",
    }

    fig, ax = plt.subplots(figsize=(8.2, 4.8), dpi=360)  # 改这里：Figure 4 的尺寸和清晰度
    for tag in ("early", "mid", "late"):
        df = normalise_line_csv(DATA_DIR / f"line_{tag}.csv")
        ax.plot(df["x"], df["p"], linewidth=2.4, label=labels_fr[tag], color=colors[tag])

    ax.set_xlabel("Position x [m]")
    ax.set_ylabel("Pression p")
    ax.set_title("Distribution de la pression le long de l'axe du reservoir")
    ax.grid(True, alpha=0.25)
    ax.legend(frameon=False)
    fig.tight_layout()
    fig.savefig(FIG_DIR / "figure4_line_plot.png", bbox_inches="tight")
    plt.close(fig)


def load_probe_data():
    tank = normalise_time_csv(DATA_DIR / "tank_over_time.csv")
    nozzle = normalise_time_csv(DATA_DIR / "nozzle_over_time.csv")
    return tank, nozzle


def build_probe_plot():
    # Figure 5：内部点和喷口点的叠加压力时间曲线。
    tank, nozzle = load_probe_data()
    fig, ax = plt.subplots(figsize=(8.2, 4.8), dpi=360)  # 改这里：Figure 5 的尺寸和清晰度
    ax.plot(tank["time"], tank["p"], linewidth=2.5, color="#1f77b4", label="Point interne")
    ax.plot(nozzle["time"], nozzle["p"], linewidth=2.5, color="#d62728", label="Point proche de la buse")
    ax.set_xlabel("Temps [s]")
    ax.set_ylabel("Pression p")
    ax.set_title("Evolution temporelle de la pression a deux positions")
    ax.grid(True, alpha=0.25)
    ax.legend(frameon=False)
    fig.tight_layout()
    fig.savefig(FIG_DIR / "figure5_probe_plot.png", bbox_inches="tight")
    plt.close(fig)


def build_chart_frames():
    # 动画右图：和 Figure 5 用同一组数据，但额外加一条移动时间线。
    labels, time_values, _ = load_time_map()
    tank, nozzle = load_probe_data()
    time_min = min(tank["time"].min(), nozzle["time"].min()) * 1.0e6
    time_max = max(tank["time"].max(), nozzle["time"].max()) * 1.0e6
    p_min = min(tank["p"].min(), nozzle["p"].min())
    p_max = max(tank["p"].max(), nozzle["p"].max())
    pad = 0.05 * (p_max - p_min if p_max > p_min else 1.0)

    for idx, _ in enumerate(labels):
        current_time = time_values[idx]
        tank_time_us = tank["time"] * 1.0e6
        nozzle_time_us = nozzle["time"] * 1.0e6
        current_time_us = current_time * 1.0e6
        fig, ax = plt.subplots(figsize=(9.0, 6.0), dpi=360)  # 改这里：动画右图原始画布大小
        ax.plot(tank_time_us, tank["p"], linewidth=2.5, color="#1f77b4", label="Point interne")
        ax.plot(nozzle_time_us, nozzle["p"], linewidth=2.5, color="#d62728", label="Point proche de la buse")
        ax.axvline(current_time_us, color="black", linestyle="--", linewidth=1.6)  # 改这里：移动时间线样式
        ax.set_xlim(time_min, time_max)
        ax.set_ylim(p_min - pad, p_max + pad)
        ax.set_xlabel("Temps [us]", fontsize=32)  # 改这里：动画右图横轴标签字号
        ax.set_ylabel("Pression p", fontsize=32)  # 改这里：动画右图纵轴标签字号
        ax.set_title("Evolution temporelle de la pression", fontsize=36)  # 改这里：动画右图标题字号
        ax.grid(True, alpha=0.25)
        ax.legend(frameon=False, loc="best", fontsize=18)  # 改这里：图例字号
        ax.tick_params(axis="both", labelsize=18)        # 改这里：坐标刻度字号

        fig.tight_layout()
        fig.savefig(CHART_FRAMES_DIR / f"frame_{idx:03d}.png", bbox_inches="tight")
        plt.close(fig)


def combine_animation_frames():
    labels, _, _ = load_time_map()
    for idx, _ in enumerate(labels):
        left = Image.open(LEFT_FRAMES_DIR / f"frame_{idx:03d}.png").convert("RGB")
        right = Image.open(CHART_FRAMES_DIR / f"frame_{idx:03d}.png").convert("RGB")

        # 这里控制左图四周还剩多少空白。
        left = left.crop((240, 0, 3000, 2360))  # 改这里：[左, 上, 右, 下]，直接控制左图裁剪范围
        # 这里控制右边折线图相对左图有多大。
        right = ImageOps.contain(right, (1400, left.height - 160))  # 改这里：右图最大宽高

        target_height = left.height
        if right.height != target_height:
            right = ImageOps.pad(right, (right.width, target_height), color="white", centering=(0.5, 0.5))

        gutter = 24  # 改这里：左右两栏中间留多少空隙
        canvas = Image.new("RGB", (left.width + right.width + gutter, target_height), "white")
        canvas.paste(left, (0, 0))
        canvas.paste(right, (left.width + gutter, 0))

        # 左右两栏之间的分隔线。
        draw = ImageDraw.Draw(canvas)
        draw.line([(left.width + gutter // 2, 20), (left.width + gutter // 2, target_height - 20)], fill=(210, 210, 210), width=2)  # 改这里：分隔线颜色和粗细

        canvas.save(COMBINED_FRAMES_DIR / f"frame_{idx:03d}.png")


def build_animation():
    # 用已经拼好的帧合成最终 mp4。
    output = ROOT / "decompressionTank.mp4"
    cmd = [
        "ffmpeg",
        "-y",
        "-framerate",
        "10",  # 改这里：最终视频帧率
        "-i",
        str(COMBINED_FRAMES_DIR / "frame_%03d.png"),
        "-c:v",
        "mpeg4",
        "-q:v",
        "1",
        "-vf",
        "scale=trunc(iw/2)*2:trunc(ih/2)*2",
        "-pix_fmt",
        "yuv420p",
        str(output),
    ]
    subprocess.run(cmd, check=True)


def build_left_animation():
    # 用左图原始帧单独合成一个 mp4，方便只检查模拟主画面。
    output = ROOT / "decompressionTank_left.mp4"
    cmd = [
        "ffmpeg",
        "-y",
        "-framerate",
        "10",  # 改这里：左图单独视频的帧率
        "-i",
        str(LEFT_FRAMES_DIR / "frame_%03d.png"),
        "-c:v",
        "mpeg4",
        "-q:v",
        "1",
        "-vf",
        "scale=trunc(iw/2)*2:trunc(ih/2)*2",
        "-pix_fmt",
        "yuv420p",
        str(output),
    ]
    subprocess.run(cmd, check=True)


def main():
    build_line_plot()
    build_probe_plot()
    build_chart_frames()
    combine_animation_frames()
    build_left_animation()
    build_animation()


if __name__ == "__main__":
    main()
