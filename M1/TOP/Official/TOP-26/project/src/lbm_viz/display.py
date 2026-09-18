from __future__ import annotations

import subprocess
from dataclasses import dataclass
from pathlib import Path


@dataclass
class FrameInfo:
    width: int
    height: int
    frames: int


class DisplayBinary:
    def __init__(self, binary_path: str = "build/display"):
        self.binary = Path(binary_path)
        if not self.binary.exists():
            raise FileNotFoundError(f"Display binary not found: {self.binary}")

    def info(self, input_file: str) -> FrameInfo:
        result = subprocess.run(
            [str(self.binary), "--info", input_file, "0"],
            capture_output=True,
            text=True,
            check=True,
        )
        info = {}
        for line in result.stdout.strip().split("\n"):
            if "=" in line:
                key, value = line.split("=")
                info[key.strip()] = int(value.strip())
        return FrameInfo(
            width=info["width"],
            height=info["height"],
            frames=info["frames"],
        )

    def gnuplot(self, input_file: str, frame: int) -> str:
        result = subprocess.run(
            [str(self.binary), "--gnuplot", input_file, str(frame)],
            capture_output=True,
            text=True,
            check=True,
        )
        return result.stdout

    def checksum(self, input_file: str, frame: int) -> str:
        result = subprocess.run(
            [str(self.binary), "--checksum", input_file, str(frame)],
            capture_output=True,
            text=True,
            check=True,
        )
        return result.stdout.strip()
