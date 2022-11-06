#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
using cards = vector<int>;

cards inputCards(const int& N)
{
  vector<int> output(N);
  for (size_t i = 0; i < N; i++)
    cin >> output[i];   // Card's values: 1 ≤ Ai, Bi ≤ N
  return output;
}

string solve()
{
  int N; cin >> N;      // No. cards N: 2 ≤ N ≤ 500,000
  int K; cin >> K;      // No. swaps K: 0 ≤ K ≤ 10e9
  cards cardsA = inputCards(N);
  cards cardsB = inputCards(N);
  if (K == 0)
    return (cardsA == cardsB) ? "YES" : "NO";
  if (K == 1 && cardsA == cardsB)
    return "NO";
  if (N == 2) {       // If there is only 2 cards
    if (K%2 == 1)     // With odd K, the order has to change
      return (cardsA != cardsB) ? "YES" : "NO";
    if (K%2 == 0)     // With even K, the order stays the same
      return (cardsA == cardsB) ? "YES" : "NO";
  }
  // Otherwise, if it's possible, it would be with 1 single cut
  auto it = find(cardsA.begin(), cardsA.end(), cardsB[0]);
  cards cardsC(it, cardsA.end());
  cardsC.insert(cardsC.end(), cardsA.begin(), it);
  return (cardsB ==  cardsC) ? "YES" : "NO";
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;    // No. cases T: 1 ≤ T ≤ 200
  for (size_t t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve() << endl;
  return 0;
}
// Time = 750[ms]