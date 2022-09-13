#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <math.h>
#include <sstream>
#include <bitset>

// The different with task C1 is that now
// the length of (N-1) codewords is between 1-10
// 
// The approach is still the same. We still have
// the binary tree and that all other (N-1)
// codewords have the same length.
// 
// Given N and codeword C1 with length L1
// We can't have other codewords of length L1,
// since L1 can be much longer 1-100.
// All other codewords will have different
// beginning char

/**
 * @brief return vector of codewords
 * 
 * @param N: number of codewords
 * @param L: length of codewords
 */
std::vector<std::string> GetCodewords(const int& N, const int& L)
{
  std::vector<std::string> codeWords;
  for (size_t i = 0; i < N; i++) {
    std::string binaryString = std::bitset<9>(i).to_string();
    std::replace(binaryString.begin(), binaryString.end(), '0', '.');
    std::replace(binaryString.begin(), binaryString.end(), '1', '-');
    codeWords.push_back(binaryString.substr(9-L, L));
  }
  return codeWords;
}

int main()
{
  std::ifstream myfileI ("second_second_meaning_input.txt");
  std::ofstream myfileO ("output.txt", std::ios::trunc);
  // T: number of test cases
  // N: number of codewords
  int T, N;

  if (myfileI.is_open() && myfileO.is_open()) {
    std::string line;
    std::getline (myfileI,line);
    T = stoi(line);
    
    // Loop over each test case
    for (size_t t = 0; t < T; t++) {
      std::getline (myfileI,line);
      N = stoi(line);
      std::string C1;
      std::getline (myfileI,C1);
      int L = ceil(log2(N));

      // Generate (N-1) codewords with length L
      // then add a different char in the beginning
      std::vector<std::string> codewords = GetCodewords(N-1, L);
      for (size_t i = 0; i < N-1; i++) {
        if (C1[0] == '.') {
          codewords[i].insert(0,"-");
        } else {
          codewords[i].insert(0,".");
        }
      }

      // Print out codewords
      myfileO << "Case #" << t + 1 <<":" << std::endl;
      for (auto codeword : codewords) {
        myfileO << codeword << "\n";
      }
    }
    myfileI.close();
    myfileO.close();
  } else std::cout << "Unable to open file for reading";
  return 0;
}
