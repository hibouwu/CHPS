from __future__ import annotations

import os
import subprocess
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path
from typing import Iterator

import psutil
from tqdm import tqdm


class GIFGenerator:
    def __init__(
        self,
        display_binary: str = "./build/top.display",
        workers: int | None = None,
        input_file: str | None = None,
    ):
        binary_path = Path(display_binary)
        if not binary_path.is_absolute() and not binary_path.exists():
            if input_file:
                input_path = Path(input_file).resolve()
                input_dir = input_path.parent
                binary_path = input_dir / display_binary
            if not binary_path.exists():
                binary_path_cwd = Path.cwd() / display_binary
                if binary_path_cwd.exists():
                    binary_path = binary_path_cwd
        if not binary_path.exists():
            raise FileNotFoundError(f"Display binary not found: {binary_path}")
        self.display_binary = binary_path
        if workers:
            self.workers = workers
        else:
            physical_cores = psutil.cpu_count(logical=False)
            self.workers = max(1, (physical_cores or os.cpu_count() or 1) - 1)

    def get_frame_count(self, input_file: str) -> int:
        result = subprocess.run(
            [str(self.display_binary), "--info", input_file, "0"],
            capture_output=True,
            text=True,
            check=True,
        )
        for line in result.stdout.strip().split("\n"):
            if "frames" in line:
                return int(line.split("=")[1].strip())
        raise ValueError("Could not determine frame count")

    def fetch_frame(self, input_file: str, frame: int) -> tuple[int, str]:
        result = subprocess.run(
            [str(self.display_binary), "--gnuplot", input_file, str(frame)],
            capture_output=True,
            text=True,
            check=True,
        )
        return (frame, result.stdout)

    def fetch_frames_parallel(self, input_file: str, frames: range) -> dict[int, str]:
        frame_data = {}
        with ThreadPoolExecutor(max_workers=self.workers) as executor:
            futures = {
                executor.submit(self.fetch_frame, input_file, f): f for f in frames
            }
            with tqdm(total=len(frames), desc="Fetching frames", unit="frame") as pbar:
                for future in as_completed(futures):
                    frame_idx, data = future.result()
                    frame_data[frame_idx] = data
                    pbar.update(1)
        return frame_data

    def fetch_checksums_parallel(
        self, input_file: str, frames: range
    ) -> dict[int, str]:
        def do_checksum(frame: int) -> tuple[int, str]:
            result = subprocess.run(
                [str(self.display_binary), "--checksum", input_file, str(frame)],
                capture_output=True,
                text=True,
                check=True,
            )
            return (frame, result.stdout.strip())

        checksums = {}
        with ThreadPoolExecutor(max_workers=self.workers) as executor:
            futures = {executor.submit(do_checksum, f): f for f in frames}
            with tqdm(
                total=len(frames), desc="Computing checksums", unit="frame"
            ) as pbar:
                for future in as_completed(futures):
                    frame_idx, checksum = future.result()
                    checksums[frame_idx] = checksum
                    pbar.update(1)
        return checksums

    def prepare_gif(
        self,
        input_file: str,
        output_file: str,
        width: int | None = None,
        height: int | None = None,
        **gnuplot_kwargs,
    ) -> tuple[float, str, tempfile.TemporaryDirectory]:
        import time
        import tempfile

        info = self.get_file_info(input_file)
        mesh_width = info.get("width", 800)
        mesh_height = info.get("height", 100)

        if width is None:
            width = max(1500, int(mesh_width * 1.8))
        if height is None:
            height = max(300, int(mesh_height * 1.8))

        fetch_start = time.time()
        frame_count = info.get("frames", 0)
        frames = range(frame_count)
        frame_data = self.fetch_frames_parallel(input_file, frames)
        fetch_time = time.time() - fetch_start

        from .gnuplot import generate_config

        temp_dir = tempfile.TemporaryDirectory()
        config, _ = generate_config(
            output_file,
            frame_data=frame_data,
            temp_dir=Path(temp_dir.name),
            width=width,
            height=height,
            **gnuplot_kwargs,
        )

        return fetch_time, config, temp_dir

    def render_gif(self, config: str) -> float:
        import subprocess
        import time

        start = time.time()
        subprocess.run(["gnuplot"], input=config, text=True, check=True)
        return time.time() - start

    def generate_gif(
        self, input_file: str, output_file: str, **gnuplot_kwargs
    ) -> tuple[float, float]:
        fetch_time, config, temp_dir = self.prepare_gif(
            input_file, output_file, **gnuplot_kwargs
        )
        try:
            render_time = self.render_gif(config)
        finally:
            temp_dir.cleanup()
        return fetch_time, fetch_time + render_time

    def print_checksums(self, input_file: str) -> None:
        frame_count = self.get_frame_count(input_file)
        checksums = self.fetch_checksums_parallel(input_file, range(frame_count))
        for frame_idx in sorted(checksums.keys()):
            print(f"Frame {frame_idx}: {checksums[frame_idx]}")

    def get_file_info(self, input_file: str) -> dict[str, int]:
        result = subprocess.run(
            [str(self.display_binary), "--info", input_file, "0"],
            capture_output=True,
            text=True,
            check=True,
        )
        info = {}
        for line in result.stdout.strip().split("\n"):
            if "=" in line:
                key, value = line.split("=")
                info[key.strip()] = int(value.strip())
        return info

    def compare(self, reference: str, input_file: str) -> int:
        reference = str(Path(reference).resolve())
        input_file = str(Path(input_file).resolve())
        ref_info = self.get_file_info(reference)
        inp_info = self.get_file_info(input_file)

        if ref_info.get("width") != inp_info.get("width"):
            print(
                f"warning: simulations have different width (base is {ref_info.get('width')} and provided simulation is {inp_info.get('width')})."
            )
        if ref_info.get("height") != inp_info.get("height"):
            print(
                f"warning: simulations have different height (base is {ref_info.get('height')} and provided simulation is {inp_info.get('height')})."
            )
        if ref_info.get("frames") != inp_info.get("frames"):
            print(
                f"warning: simulations have different frames (base is {ref_info.get('frames')} and provided simulation is {inp_info.get('frames')})."
            )

        ref_frames = min(ref_info.get("frames", 0), inp_info.get("frames", 0))
        frames = range(ref_frames)

        ref_checksums = self.fetch_checksums_parallel(reference, frames)
        inp_checksums = self.fetch_checksums_parallel(input_file, frames)

        code = 0
        for frame_idx in sorted(ref_checksums.keys()):
            ref_cs = ref_checksums[frame_idx]
            inp_cs = inp_checksums[frame_idx]
            if ref_cs != inp_cs:
                print(f"failure: checksum is incorrect for frame {frame_idx}.")
                print(f"  Reference is: {ref_cs}")
                print(f"  Input is:     {inp_cs}")
                code = 1

        if code == 0:
            print("ok")

        return code

    def generate_png(
        self,
        input_file: str,
        output_file: str,
        frame: int | None = None,
        cbr_min: float = 0.0,
        cbr_max: float = 0.14,
    ) -> float:
        import tempfile
        import subprocess
        import time

        start = time.time()

        info = self.get_file_info(input_file)
        mesh_width = info.get("width", 800)
        mesh_height = info.get("height", 100)

        if frame is None:
            frame = info.get("frames", 1) - 1

        width = int(mesh_width * 1.2)
        height = int(mesh_height * 1.2)

        frame_data = self.fetch_frame(input_file, frame)[1]

        with tempfile.TemporaryDirectory() as temp_dir:
            from .gnuplot import generate_png_config

            config, temp_file = generate_png_config(
                output_file,
                width=width,
                height=height,
                cbr_min=cbr_min,
                cbr_max=cbr_max,
                frame_data=frame_data,
                temp_dir=Path(temp_dir),
            )
            subprocess.run(["gnuplot"], input=config, text=True, check=True)

        return time.time() - start
