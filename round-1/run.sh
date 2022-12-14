#!/bin/bash

# Done: a1, a2, b1, b2, c
# Undone:
clear
g++     c.cpp -o out
./out < c.txt #> output.txt
rm -f out
