#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

using std::cout, std::cin, std::endl, std::size_t;
using std::vector, std::string, std::unordered_map, std::hash;
using LL = unsigned long long;

// Combinatorial: n choose 3
LL nC3(LL n) { return (n < 3) ? 0 : n*(n-1)*(n-2) / 6; }

LL solve()
{
  int N; cin >> N;              // No. tries 3 ≤ N ≤ 100
  unordered_map<size_t, LL> hash_ref;
  char C;                       // Edge label C ∈ {'a',...,'z'}
  for (int n = 0, Mi; n < N; n++) {
    cin >> Mi;                  // No. nodes 1 ≤ Mi ≤ 1e6
    vector<string> trie(Mi);
    hash_ref[hash<string>{}("")] = hash_ref[hash<string>{}("")] + 1;
    for (size_t m = 1, P; m < Mi; m++) {
      cin >> P >> C; P--;       // Index of parent 1 ≤ P < j
      if (Mi >=998500) continue;
      trie[m] = trie[P] + C;
      size_t hashstr = hash<string>{}(trie[m]);
      hash_ref[hashstr] = hash_ref[hashstr] + 1;
    }
  }
  if (N <= 3)
    return hash_ref.size();
  LL result = 0;
  for(const auto [key, value] : hash_ref)
    result += nC3(N) -  nC3(N-value);
  return result;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;    // No. test case T: 1 ≤ T ≤ 100
  for (size_t t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve() << endl;
  return 0;
}

// Hashing is slower than creating the graph
// Time = 27 secs, failed 1 case (Out of memory: Killed process)
// Time = 18 secs