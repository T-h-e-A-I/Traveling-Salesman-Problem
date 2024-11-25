#!/bin/bash

set -e

# Create build and output directories
mkdir -p build

# Compile the program
g++ -std=c++17 -o build/tsp_solver \
    main.cpp \
    point.cpp \
    tspParser.cpp \
    constructiveHeuristics.cpp \
    perturbativeHeursitics.cpp \
    tspsolver.cpp

if [ $? -eq 0 ]; then
    echo "Compilation successful! Processing input files..."
    
    # Create output file
    > output.txt
    
    # Process each file in the input directory
    for input_file in input/*; do
        echo $input_file
        if [ -f "$input_file" ]; then
            echo "Processing: $input_file"
            echo "=== Results for $input_file ===" >> output.txt
            ./build/tsp_solver "$input_file" >> output.txt
            echo -e "\n" >> output.txt
        fi
    done
    
    echo "Processing complete! Results stored in output.txt"
else
    echo "Compilation failed!"
    exit 1
fi
