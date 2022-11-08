#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
const int S = 100;

string solve()
{
  int N; cin >> N;                  // No. parts N: 1 ≤ N ≤ 100.
  int K; cin >> K;                  // Case capacity K: 1 ≤ K ≤ 100
  vector<int> vectPart(N);          // Input part indices
  for (int n = 0; n < N; n++)
    cin >> vectPart[n];             // Part index Si: 1 ≤ Si ≤ 100
  if (N > 2*K) return "NO";         // Criterion 1: N < 2K
  std::vector<int> partCounts(S+1); // Counts of each part type
  for (size_t s = 0; s <= S; s++)
    partCounts[s] = count(vectPart.begin(), vectPart.end(), s);
  int maxCount = *max_element(partCounts.begin(), partCounts.end());
  if (maxCount > 2) return "NO";    // Criterion 2: no more than 2 same items
  return "YES";
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;                  // No. test case T: 1 ≤ T ≤ 90
  for (int t = 1, N, K; t <= T; t++)
    cout << "Case #" << t << ": " << solve() << endl;
  return 0;
}
// Time t = 7[ms]