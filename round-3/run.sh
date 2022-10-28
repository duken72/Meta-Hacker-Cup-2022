#!/bin/bash

clear
# g++ a.cpp -o out && ./out < a.txt > output.txt
# g++ b.cpp -o out && ./out < b.txt #> output.txt
g++ b_sol.cpp -o out && ./out < b.txt #> output.txt
# g++ c.cpp -o out && ./out < c.txt #> output.txt
# g++ d1.cpp -o out && ./out < d1.txt #> output.txt
# g++ d2.cpp -o out && ./out < d2.txt #> output.txt
# g++ e1.cpp -o out && ./out < e1.txt #> output.txt
# g++ e2.cpp -o out && ./out < e2.txt #> output.txt
# Finished: a
# Unfinished: b, c, d1, d2, e1, e2
rm -f out
