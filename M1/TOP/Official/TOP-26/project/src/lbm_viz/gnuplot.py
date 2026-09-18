from __future__ import annotations

import tempfile
from pathlib import Path


def generate_config(
    output_file: str,
    width: int = 1700,
    height: int = 300,
    delay: int = 2,
    cbr_min: float = 0.0,
    cbr_max: float = 0.14,
    frame_data: dict[int, str] | None = None,
    temp_dir: Path | None = None,
) -> tuple[str, list[Path]]:
    lines = []
    lines.append("set pm3d map")
    lines.append(
        "set palette defined ("
        "0 '#000090', "
        "1 '#000fff', "
        "2 '#0090ff', "
        "3 '#0fffee', "
        "4 '#90ff70', "
        "5 '#ffee00', "
        "6 '#ff7000', "
        "7 '#ee0000', "
        "8 '#7f0000')"
    )
    lines.append(f"set cbr [{cbr_min}:{cbr_max}]")
    lines.append(f"set term gif animate delay {delay} size {width},{height}")
    lines.append(f"set output '{output_file}'")

    temp_files: list[Path] = []

    if frame_data:
        for frame_idx in sorted(frame_data.keys()):
            if temp_dir is None:
                fd, temp_path = tempfile.mkstemp(suffix=f"_frame_{frame_idx:04d}.dat")
            else:
                temp_path = Path(temp_dir) / f"frame_{frame_idx:04d}.dat"
            with open(temp_path, "w") as f:
                f.write(frame_data[frame_idx])
            temp_files.append(Path(temp_path))
            lines.append(f'splot "{temp_path}" u 1:2:4')

    return "\n".join(lines) + "\n", temp_files


def generate_png_config(
    output_file: str,
    width: int,
    height: int,
    cbr_min: float = 0.0,
    cbr_max: float = 0.14,
    frame_data: str | None = None,
    temp_dir: Path | None = None,
) -> tuple[str, Path]:
    lines = []
    lines.append("set pm3d map")
    lines.append(
        "set palette defined ("
        "0 '#000090', "
        "1 '#000fff', "
        "2 '#0090ff', "
        "3 '#0fffee', "
        "4 '#90ff70', "
        "5 '#ffee00', "
        "6 '#ff7000', "
        "7 '#ee0000', "
        "8 '#7f0000')"
    )
    lines.append(f"set cbr [{cbr_min}:{cbr_max}]")
    lines.append(f"set term png size {width},{height}")
    lines.append(f"set output '{output_file}'")
    lines.append("unset colorbox")
    lines.append("unset tics")
    lines.append("unset key")
    lines.append("set lmargin 0")
    lines.append("set rmargin 0")
    lines.append("set tmargin 0")
    lines.append("set bmargin 0")
    lines.append("set size 1,1")
    lines.append("set origin 0,0")

    if frame_data:
        if temp_dir is None:
            fd, temp_path = tempfile.mkstemp(suffix=".dat")
        else:
            temp_path = Path(temp_dir) / "frame.dat"
        with open(temp_path, "w") as f:
            f.write(frame_data)
        lines.append(f'splot "{temp_path}" u 1:2:4')

    return "\n".join(lines) + "\n", Path(temp_path)
