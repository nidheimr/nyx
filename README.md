# Nyx

## Overview

Nyx is a simple voxel game with my own rendering library [Lux](https://github.com/nidheimr/lux).

It was written for educational purposes and is likely not very efficient.

## Building

This project uses CMake. The only supported platforms for this project are: Windows (10+), Linux (Wayland).

Assuming you have CMake and a C compiler, you can run the following commands inside the project directory:
1. `cmake -S . -B build`
2. `cmake --build build`

This will build the executable and and place it inside `./bin/`.
