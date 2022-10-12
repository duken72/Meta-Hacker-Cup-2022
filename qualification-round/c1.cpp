#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>
#include <math.h>

using std::cout, std::cin, std::endl;
using std::vector, std::string;
using std::replace, std::bitset;

// Build a binary tree of possible codewords
// Each node represents a codeword.
//    -       .         1 char    2 nodes = 2^(1+1)
//  -   .   -   .       2 chars   4 nodes = 2^(2+1)
// - . - . - . - .      3 chars   8 nodes = 2^(3+1)
// Codewords with same length will be an unambiguous encoding

// Return vector of N codewords of length L
vector<string> GetCodewords(const int& N, const int& L)
{
  std::vector<std::string> codeWords;
  for (size_t i = 0; i < N; i++) {
    string binaryString = bitset<200>(i).to_string();
    replace(binaryString.begin(), binaryString.end(), '0', '.');
    replace(binaryString.begin(), binaryString.end(), '1', '-');
    codeWords.push_back(binaryString.substr(200-L, L));
  }
  return codeWords;
}

void solve(const int& N, const string& C1)
{
  // The length for enough codewords of same length
  int L = ceil(log2(N));
  int L1 = C1.length();     // length of C1
  vector<string> codewords;

  if (L1 >= L) {
    codewords = GetCodewords(N, L1);
    // Remove if C1 is in the list
    for (size_t i = 0; i < N; i++) {
      if (codewords[i] == C1) {
        codewords.erase(codewords.begin() + i);
        break;
      }
    }
    if (codewords.size() == N)
      codewords.erase(codewords.begin());    
  } else {    // If L1 < L
    // Take other (N-1) words with length L+1
    // and have a different beginning character than C1.
    codewords = GetCodewords(N-1, L);
    string startChar = (C1[0] == '.') ? "-" : ".";
    for (size_t i = 0; i < N-1; i++)
      codewords[i].insert(0, startChar);
  }
  for (auto word : codewords)
    cout << word << endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T; cin >> T;          // No. test cases T: 1 ≤ T ≤ 100
  for (size_t t = 1; t <= T; t++) {
    int N; cin >> N;        // No. codewords N: 2 ≤ N ≤ 100
    string C1; cin >> C1;   // 1st codeword
    cout << "Case #" << t << ":\n";
    solve(N, C1);
  }
  return 0;
}
