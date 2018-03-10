#!/bin/sh

MAIN="main.cpp"
INPUT="input.h input.cpp"
OBJECT="object.h object.cpp"
RENDERER="renderer.h renderer.cpp"

FLAGS="-lSDL2 -lSDL2_image -std=c++17"

g++ -o main $MAIN $INPUT $OBJECT $RENDERER $FLAGS