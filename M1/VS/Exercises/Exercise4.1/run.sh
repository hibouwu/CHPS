#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
if [[ -n "${PARAVIEW_BIN:-}" ]]; then
    MPIEXEC="$PARAVIEW_BIN/mpiexec"
    PVBATCH="$PARAVIEW_BIN/pvbatch"
else
    MPIEXEC="$(command -v mpiexec || true)"
    PVBATCH="$(command -v pvbatch || true)"
fi
if [[ ! -x "$MPIEXEC" || ! -x "$PVBATCH" ]]; then
    echo "Set PARAVIEW_BIN to the ParaView bin directory, or add mpiexec and pvbatch to PATH." >&2
    exit 1
fi
"$MPIEXEC" -n 4 "$PVBATCH" "$SCRIPT_DIR/parasphere.py"
