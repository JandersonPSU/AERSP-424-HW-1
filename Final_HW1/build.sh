#!/bin/bash

# Remove old build directory if it exists
rm -rf build

# Create a new build directory
mkdir build
cd build

# Run CMake to configure the project
cmake ..

# Run make to build the project
make
