#!/bin/bash

clear
# g++ A1.cpp -o out && ./out < a1_input.txt
# g++ A2.cpp -o out && ./out < a2_sample_input.txt
# g++ A2.cpp -o out && ./out < a2_input.txt > output.txt
# g++ B1.cpp -o out && ./out < b1_sample_input.txt
# g++ B2.cpp -o out && ./out < b2_sample_input.txt
# g++ C.cpp -o out && ./out < c_input.txt
# g++ D1.cpp -o out && ./out < d1_input.txt
# g++ D2.cpp -o out && ./out < 1.txt
g++ D2.cpp -o out && ./out < d2_sample_input.txt #> output.txt

# g++ test.cpp -o out && ./out
rm -f out
# > output.txt