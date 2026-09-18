from __future__ import annotations

import argparse
import sys
import time

from rich.console import Console
from rich.status import Status

from .generator import GIFGenerator

console = Console()


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        prog="lbm-viz",
        description="Visualize LBM simulation results as animated GIFs",
    )

    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument(
        "--generate-gif",
        nargs=2,
        metavar=("INPUT", "OUTPUT"),
        help="Generate GIF from input .raw file",
    )
    mode.add_argument(
        "--check",
        nargs=2,
        metavar=("REFERENCE", "INPUT"),
        help="Compare INPUT against REFERENCE file checksums",
    )
    mode.add_argument(
        "--png",
        nargs=2,
        metavar=("INPUT", "OUTPUT"),
        help="Extract single frame as PNG from input .raw file",
    )

    parser.add_argument(
        "-j",
        "--workers",
        type=int,
        default=None,
        help="Number of parallel workers (default: CPU count)",
    )
    parser.add_argument(
        "-d",
        "--delay",
        type=int,
        default=2,
        help="GIF frame delay in centiseconds (default: 2)",
    )
    parser.add_argument(
        "-s",
        "--size",
        nargs=2,
        type=int,
        default=None,
        metavar=("WIDTH", "HEIGHT"),
        help="Output size (default: auto based on image dimensions)",
    )
    parser.add_argument(
        "--frame",
        type=int,
        default=None,
        help="Frame index to extract (default: last frame for PNG, not used for GIF)",
    )
    parser.add_argument(
        "--cbr",
        nargs=2,
        type=float,
        default=[0.0, 0.14],
        metavar=("MIN", "MAX"),
        help="Colorbar range (default: 0.0 0.14)",
    )
    parser.add_argument(
        "--display-bin-path",
        default="./build/top.display",
        help="Path to display binary (default: ./build/top.display)",
    )

    return parser.parse_args()


def main() -> int:
    args = parse_args()

    try:
        if args.generate_gif:
            input_file, output_file = args.generate_gif
            generator = GIFGenerator(
                display_binary=args.display_bin_path,
                workers=args.workers,
                input_file=input_file,
            )

            console.print(
                f"[bold blue]==>[/bold blue] Generating [magenta]{output_file}[/magenta]..."
            )

            fetch_time, config, temp_dir = generator.prepare_gif(
                input_file,
                output_file,
                width=args.size[0] if args.size else None,
                height=args.size[1] if args.size else None,
                delay=args.delay,
                cbr_min=args.cbr[0],
                cbr_max=args.cbr[1],
            )

            console.print(f"  Fetched frames in [cyan]{fetch_time:.2f}s[/cyan]")

            try:
                with Status("Rendering GIF...", console=console):
                    render_time = generator.render_gif(config)
            finally:
                temp_dir.cleanup()

            total_time = fetch_time + render_time
            console.print(
                f"\n[green]Finished[/green] generating GIF in [cyan]{total_time:.2f}s[/cyan]"
            )
            console.print(f"[bold green][+][/bold green] {output_file}")

        elif args.check:
            reference, input_file = args.check
            generator = GIFGenerator(
                display_binary=args.display_bin_path,
                workers=args.workers,
                input_file=reference,
            )
            return generator.compare(reference, input_file)

        elif args.png:
            input_file, output_file = args.png
            generator = GIFGenerator(
                display_binary=args.display_bin_path,
                workers=args.workers,
                input_file=input_file,
            )

            console.print(
                f"[bold blue]==>[/bold blue] Extracting frame to [magenta]{output_file}[/magenta]..."
            )

            with Status("Rendering PNG...", console=console):
                elapsed = generator.generate_png(
                    input_file,
                    output_file,
                    frame=args.frame,
                    cbr_min=args.cbr[0],
                    cbr_max=args.cbr[1],
                )

            console.print(
                f"\n[green]Finished[/green] generating PNG in [cyan]{elapsed:.2f}s[/cyan]"
            )
            console.print(f"[bold green][+][/bold green] {output_file}")

        return 0

    except FileNotFoundError as e:
        console.print(f"[bold red]Error:[/bold red] {e}")
        return 1
    except Exception as e:
        console.print(f"[bold red]Error:[/bold red] {e}")
        return 1


if __name__ == "__main__":
    sys.exit(main())
