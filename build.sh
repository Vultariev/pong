#!/bin/bash
## Usage: build.sh [OUTPUTFILENAME]
gcc `sdl2-config --libs --cflags` -I"Resources/include" -lm main.c clamp.c -o pong
