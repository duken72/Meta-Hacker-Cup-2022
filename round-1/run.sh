#!/bin/bash

# Finished: a1, a2, b1, b2, c
clear
g++ c_alt.cpp -o out && ./out < c.txt #> output.txt
rm -f out
