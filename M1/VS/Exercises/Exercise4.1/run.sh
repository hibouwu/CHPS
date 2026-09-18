#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PARAVIEW_BIN="${PARAVIEW_BIN:-/home/jianyeshi/Note/Visualization scientufique/ParaView-6.1.0-RC1-MPI-Linux-Python3.12-x86_64/bin}"

"$PARAVIEW_BIN/mpiexec" -n 4 \
  "$PARAVIEW_BIN/pvbatch" \
  "$SCRIPT_DIR/parasphere.py"
