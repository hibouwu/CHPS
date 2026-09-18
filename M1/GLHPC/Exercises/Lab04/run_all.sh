#!bash

if [ -z "$1" ]; then
    echo "Usage: $0 <output_label>"
    exit 1
fi

set -e
set -o pipefail


OUTPUT_DIR="results/$1"
mkdir -p $OUTPUT_DIR


if [ ! -d "venv" ]; then
    echo "Creating virtual environment..."
    virtualenv ./venv
    source ./venv/bin/activate
    pip install pandas numpy rich matplotlib seaborn tqdm
else
    echo "Using existing virtual environment..."
    source ./venv/bin/activate
fi

{
    echo "Building the project..."

    cd build
    

    # Build the project
    make
    # Check whether the executable was built
    if [ ! -f piestimator ]; then
        echo "Error: piestimator not found. Please check the build process."
        exit 1
    fi

    echo "Collecting env information"
    date > "../$OUTPUT_DIR/timestamp.txt"
    cat /proc/cpuinfo > "../$OUTPUT_DIR/cpuinfo.txt"
    cat /proc/meminfo > "../$OUTPUT_DIR/meminfo.txt"
    echo $1 > "../$OUTPUT_DIR/label.txt"

    echo "Running the analysis scripts..."
    ../scripts/analyse.py ../$OUTPUT_DIR

    echo "Done!"
} 2>&1 | tee $OUTPUT_DIR/run_all.log