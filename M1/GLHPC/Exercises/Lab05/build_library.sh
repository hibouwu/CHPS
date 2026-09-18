#!/bin/bash

set -e
set -o pipefail

current_dir=$(dirname $0)

if ! command -v cmake &> /dev/null; then
    echo "cmake could not be found, please install it"
    echo "On Fedora:"
    echo "sudo dnf install cmake gcc"
    echo "On Ubuntu:"
    echo "sudo apt install cmake gcc"
    exit 1
fi

cmake -S ./libbls -B ./libbls/build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$current_dir/libbls/install
cmake --build ./libbls/build --target install
