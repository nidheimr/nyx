# Nyx

## Overview

Nyx is a simple application that creates a window using win32 then draws a triangle using OpenGL 3.3 Core. It was written for educational purposes and is likely not very efficient.

## Building

This project uses CMake.

Assuming you have CMake installed and some form of windows C compiler (such as MSVC), you can run the following commands inside the project directory:
1. `cmake -S . -B build`
2. `cmake --build build`

The executable will be placed inside `./bin/`.
