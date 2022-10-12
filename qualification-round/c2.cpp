#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>
#include <math.h>

using std::cout, std::cin, std::endl;
using std::vector, std::string;
using std::replace, std::bitset;

// Now the length of (N-1) codewords is between 1-10
// Still find all other (N-1) codewords of the same length
// with different beginning char than C1

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
  vector<string> codewords = GetCodewords(N-1, L);
  string startChar = (C1[0] == '.') ? "-" : ".";  
  for (auto& word : codewords) {
    word.insert(0, startChar);
    cout << word << endl;
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T; cin >> T;          // No. test cases T: 1 ≤ T ≤ 95
  for (size_t t = 1; t <= T; t++) {
    int N; cin >> N;        // No. codewords N: 2 ≤ N ≤ 100
    string C1; cin >> C1;   // 1st codeword
    cout << "Case #" << t << ":\n";
    solve(N, C1);
  }
  return 0;
}
