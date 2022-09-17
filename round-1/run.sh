#!/bin/bash

# g++ A1.cpp -o out
# g++ A2.cpp -o out
# g++ B1.cpp -o out
# g++ B2.cpp -o out
g++ C.cpp -o out
# g++ dijkstra.cpp -o out

./out
rm out

# cmake -S . -B build
# cd build
# make && ./C