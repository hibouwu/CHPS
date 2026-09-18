# TOP-26: Remise du projet

**Optimisation d'un solveur D2Q9 Lattice Boltzmann hybride MPI + OpenMP pour le sillage de Karman.**

Cette archive contient le code source du solveur, l'outil de visualisation et le rapport de synthese. La description academique du sujet initial est disponible [ici](https://dssgabriel.github.io/CHP203-TOP/project/).

## Note de remise

- Rapport PDF : `rapport/report.pdf`
- Code source principal : `src/`, `include/`, `CMakeLists.txt`
- Fichier de configuration d'exemple : `config.txt`
- Outil de visualisation/validation : `src/lbm_viz/`

## Prerequis

**Simulation**

- Compilateur C++
- CMake 3.25+
- Implementation MPI compatible MPI 3.0+
- OpenMP 4.0+

**Validation et visualisation**

- Python 3.10+
- [uv](https://github.com/astral-sh/uv)
- Gnuplot
- Binaire `top.display` compile

## Compiler et executer

**Compilation du solveur**

```bash
# Configuration
cmake -B build

# Compilation du solveur principal
cmake --build build -t top.lbm-exe
```

**Execution**

```bash
# Exemple d'execution avec 2 processus MPI
mpirun -np 2 ./build/top.lbm-exe config.txt
```

Le programme lit les parametres depuis le fichier `config.txt` et ecrit un fichier de sortie `.raw` si `output_filename` est defini.

**Compilation du programme d'affichage**

```bash
# Si necessaire, dans le meme dossier de build
cmake --build build -t top.display
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
