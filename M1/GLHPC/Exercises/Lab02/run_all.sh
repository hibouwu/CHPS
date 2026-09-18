#!bash

# This script will setup the virtual environment, install dependencies, and run the experiment script.

set -e
set -o pipefail

# Expect one argument
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <version>"
    exit 1
fi

VERSION=$1

# Create a virtual environment if it doesn't exist
if [ ! -d "venv" ]; then
    virtualenv venv
    source ./venv/bin/activate
    pip install pandas numpy matplotlib seaborn rich
else
    echo "Using existing virtual environment."
    source ./venv/bin/activate
fi

mkdir -p ./results/$VERSION
./scripts/experiment.py ./results/$VERSION
