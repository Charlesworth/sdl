#!/bin/sh

MAIN="main.cpp"
INPUT="input.h input.cpp"
PLAYER="player.h player.cpp"

FLAGS="-lSDL2 -lSDL2_image -std=c++11"

g++ -o main $MAIN $INPUT $PLAYER $FLAGS