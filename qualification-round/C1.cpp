#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <sstream>
#include <bitset>
#include <algorithm>

// Build a binary tree of possible codewords
// 
//    -       .         1 char    2 nodes = 2^(1+1)
//  -   .   -   .       2 chars   4 nodes = 2^(2+1)
// - . - . - . - .      3 chars   8 nodes = 2^(3+1)
// 
// Each node represents a codeword.
// The deeper the node, the longer the codeword.
// The deeper the layer, the more nodes / words we have.
// 
// It would be an unambiguous encoding if all codewords
// have the same length.

// Given N and C1 with length L1
// 1. Find the minimum depth D that has 2^(D+1) > N code 
// words of length L=D
//   2. If L1 = L, take other (N-1) words with length L1=L
//   3. If L1 > L, take other (N-1) words with length L1
//   4. If L1 < L, take other (N-1) words with length L+1
//   and have a different beginning character than C1.
//    E.g.: C1 is .----, than the other would start with -
//    Idea: get (N-1) words with length L, than add
//    the different char to the beginning

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
    std::string binaryString = std::bitset<200>(i).to_string();
    std::replace(binaryString.begin(), binaryString.end(), '0', '.');
    std::replace(binaryString.begin(), binaryString.end(), '1', '-');
    codeWords.push_back(binaryString.substr(200-L, L));
  }
  return codeWords;
}

int main()
{
  std::ifstream myfileI ("second_meaning_input.txt");
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
      int L1 = C1.length();

      myfileO << "Case #" << t + 1 <<":" << std::endl;

      std::vector<std::string> codewords;
      if (L1 >= L) {
        codewords = GetCodewords(N, L1);
        // Check if C1 is already in the codewords, if yes, remove
        for (size_t i = 0; i < N; i++) {
          if (codewords[i] == C1) {
            codewords.erase(codewords.begin() + i);
            break;
          }
        }        
      } else {
        codewords = GetCodewords(N-1, L);
        for (size_t i = 0; i < N-1; i++) {
          if (C1[0] == '.') {
            codewords[i].insert(0,"-");
          } else {
            codewords[i].insert(0,".");
          }
        }
      }

      // Print out codewords
      for (size_t i = 0; i < N-1; i++) {
        myfileO << codewords[i] << "\n";
      }
    }
    myfileI.close();
    myfileO.close();
  } else std::cout << "Unable to open file for reading";
  return 0;
}
