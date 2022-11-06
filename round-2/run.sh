#!/bin/bash

# Finished: a1, a2, c, d1, d2
# Unfinished: b
clear
g++ a1.cpp -o out && ./out < a1.txt #> output.txt
rm -f out
