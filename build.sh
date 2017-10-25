#!/bin/bash
## Usage: build.sh [OUTPUTFILENAME]
gcc `sdl2-config --libs --cflags` $1.c -o $1
