#!/bin/sh

echo "Building for codeql $(date)" 

# Clean the build directory
make clean
#build it
make build-codeql
