#!/bin/bash

# Done: a, b1, b2, c1, c2
# Undone: d
clear
g++     d.cpp -o out
./out < d.txt #> output.txt
rm -f out
