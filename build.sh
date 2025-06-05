#!/bin/bash

# generate cmake files
cmake -S . -B build

# build the project
cmake --build build

# if flag '-r' supplied, run from res/
if [[ "$1" == "-r" ]]; then
    cd res/
    ../bin/nyx
fi
