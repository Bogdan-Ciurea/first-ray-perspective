#!/bin/bash

# check if the build directory exists
if [ ! -d "build" ]; then
    mkdir build
fi

cd build

# check if the makefile exists

if [ ! -f "Makefile" ]; then
    cmake ..
fi

# make the project and go back to the root directory
make
cd ..

# check
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./build/test-first-ray-perspective
