#!/bin/bash

# Done: a1, a2, c, d1, d2
# Undone: b
clear
g++     c.cpp -o out
./out < c.txt #> output.txt
rm -f out
