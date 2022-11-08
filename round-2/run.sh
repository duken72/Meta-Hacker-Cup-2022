#!/bin/bash

# Finished: a1, a2, c, d1, d2
# Unfinished: b
clear
g++ b.cpp -o out && ./out < b.txt #> output.txt
rm -f out
