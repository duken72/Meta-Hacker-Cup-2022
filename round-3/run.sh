#!/bin/bash

clear
g++ a.cpp -o out && ./out < a.txt #> output.txt

rm -f out
