#!/usr/bin/env bash
# To use: source setup_env.sh

if ! command -v python3 &> /dev/null; then
    echo "python3 could not be found, please install it"
    echo "On Fedora:"
    echo "sudo dnf install python3 python3-venv python3-pip python3-devel"
    echo "On Ubuntu:"
    echo "sudo apt install python3 python3-venv python3-pip python3-dev"
    return 1
fi

if ! command -v pip3 &> /dev/null; then
    echo "pip3 could not be found, please install it"
    echo "On Fedora:"
    echo "sudo dnf install python3-pip"
    echo "On Ubuntu:"
    echo "sudo apt install python3-pip"
    return 1
fi


if [ ! -d "./venv" ]; then
    echo "Creating virtual environment in ./venv"
    python3 -m venv ./venv
    source "./venv/bin/activate"
    pip install --upgrade pip
    pip install numpy pandas matplotlib seaborn tqdm scipy psutil jupyter
else
    source "./venv/bin/activate"
fi

# Get the directory of this script
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
export PYTHONPATH="$PYTHONPATH:$SCRIPT_DIR/libbls/install"
echo "Environment setup complete. Virtual environment 'venv' is activated."