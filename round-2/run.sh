#!/bin/bash

clear
# g++ a1.cpp -o out && ./out < a1.txt #> output.txt
# g++ a2.cpp -o out && ./out < a2.txt #> output.txt
# g++ a2-2.cpp -o out && ./out < a2.txt #> output.txt
g++ b.cpp -o out && ./out < b.txt #> output.txt
# g++ c.cpp -o out && ./out < c.txt #> output.txt
# g++ d1.cpp -o out && ./out < d1.txt #> output.txt
# g++ d2.cpp -o out && ./out < d2.txt #> output.txt
# Finished: a1, a2, c, d1, d2
# Unfinished: b
rm -f out
