#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using std::cout, std::cin, std::endl;
using std::vector, std::count, std::max_element, std::string;
const int S = 100;

/**
 * Check if it's possible to setup the display case
 * It would be impossible if:
 * 1. If the number of part N is greater than the capacity of two case 2K
 * 2. If there is more than 2 items of the same style
 */
string solve(const int& N, const int& K, const vector<int>& vectPart)
{
  if (N > 2*K) return "NO";         // Criteria 1    
  std::vector<int> partCounts;      // Counts of each part type
  for (size_t s = 0; s <= S; s++)
    partCounts.push_back(count(vectPart.begin(), vectPart.end(), s));
  int maxCount = *max_element(partCounts.begin(), partCounts.end());
  if (maxCount > 2) return "NO";    // Criteria 2    
  return "YES";
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T; cin >> T;    // No. test case T: 1 ≤ T ≤ 90
  int N;              // No. parts N: 1 ≤ N ≤ 100
  int K;              // Capacity of each case K: 1 ≤ K ≤ 100
  int Si;             // Part index Si: 1 ≤ Si ≤ 100
  for (size_t t = 1; t <= T; t++) {
    cin >> N >> K;
    vector<int> vectPart;         // Input part indices
    for (size_t n = 0; n < N; n++) {
      cin >> Si;
      vectPart.push_back(Si);
    }
    cout << "Case #" << t << ": " << solve(N, K, vectPart) << endl;
  }
  return 0;
}
