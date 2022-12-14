#!/bin/bash

# Done: a, b, 
# Undone: c, d1, d2, e1, e2
clear
g++     b.cpp -o out
./out < b.txt #> output.txt
rm -f out
