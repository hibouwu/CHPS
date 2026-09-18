# TOP-26: Project

**Optimization of an hybrid parallel D2Q9 lattice Boltzmann solver for Kármán vortex street.**

A complete description and instructions for the project are available [here](https://dssgabriel.github.io/CHP203-TOP/project/).

## Requirements

**Simulation:**

- C++ compiler
- CMake 3.25+
- MPI implementation (conforming to MPI 3.0+ standard)
- OpenMP (conforming to OpenMP 4.0+ specification)

**Validation and visualization:**

- Python 3.10+
- [uv](https://github.com/astral-sh/uv)
- Gnuplot
- Compiled `top.display` binary

## Build & Run

**Simulation**

Build:
```bash
# Configure
cmake -B <BUILD_DIR>

# Compile
cmake --build <BUILD_DIR> -t top.lbm-exe
```

Run:
```bash
# Execute with 512 MPI processes
mpirun -np 512 ./<BUILD_DIR>/top.lbm-exe <CONFIG_FILE>
```

**Display helper program**

```bash
# Configure
cmake -B <BUILD_DIR>

# Compile
cmake --build <BUILD_DIR> -t top.display
```

## Configuration file

The simulation is configured using a simple `config.txt` text file in the following format:
```
iterations           = 20000
width                = 800
height               = 160
obstacle_x           = 100.0
obstacle_y           = 80.0
obstacle_r           = 11.0
reynolds             = 100
inflow_max_velocity  = 0.18
output_filename      = results.raw
write_interval       = 100
```

The parameters are:

| Parameter | Description |
| --- | --- |
| `iterations` | Number of time steps |
| `width` | Total width of the mesh |
| `height` | Total height of the mesh |
| `obstacle_x` | X-axis position of the obstacle |
| `obstacle_y` | Y-axis position of the obstacle |
| `obstacle_r` | Radius of the obstacle |
| `reynolds` | Ratio of inertial to viscous forces governing the laminar to turbulent transition regime of the flow |
| `inflow_max_velocity` | Maximum inlet flow velocity |
| `output_filename` | Path of the output `.raw` file (no write if undefined) |
| `write_interval` | Number of time step between writes to the output file |


## Validate & Visualize

An `lbm-viz` tool is provided to help you validate and visualize LBM simulation results as GIFs.

**Local installation**

```bash
uv pip install -e .
```

**Usage**

Compare two files (verify checksums):
```bash
lbm-viz --check ref_results.raw <INPUT>.raw
```
_Run this regularly to validate that your changes don't affect the results of the simulation!_

Generate GIF from `.raw` file:
```bash
lbm-viz --generate-gif <INPUT>.raw <OUTPUT>.gif
```

Extract frames as PNG:
```bash
# Defaults to extracting the last frame
lbm-viz --png <INPUT>.raw <OUTPUT>.png

# Extract specific frame as PNG
lbm-viz --png <INPUT>.raw <OUTPUT>.png --frame 0
```

**Options**

| Option | Description | Default |
|--------|-------------|---------|
| `--generate-gif INPUT OUTPUT` | Generate GIF from .raw file | - |
| `--png INPUT OUTPUT` | Extract frame as PNG | - |
| `--check REFERENCE INPUT` | Compare INPUT against REFERENCE | - |
| `--frame N` | Frame index for PNG (0-indexed) | Last frame |
| `-j, --workers N` | Number of parallel workers | Physical cores - 1 |
| `-d, --delay N` | GIF frame delay (centiseconds) | 2 |
| `-s WIDTH HEIGHT` | Output dimensions for GIF | Auto (mesh × 1.8) |
| `--cbr MIN MAX` | Colorbar range | 0.0 - 0.14 |
| `--display-bin-path` | Path to display binary | `./build/top.display` |

**Development**

To run directly without installing locally:
```bash
uv run python -m lbm_viz --generate-gif results.raw test.gif
```
