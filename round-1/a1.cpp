#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout, std::cin, std::endl;
using std::vector, std::string, std::find;
using cards = vector<int>;

cards inputCards(const int& N)
{
  vector<int> output;
  int val=0;      // 1 ≤ Ai, Bi ≤ N
  for (size_t i = 0; i < N; i++) {
    cin >> val;
    output.push_back(val);
  }
  return output;
}

string solve(const int& K, const cards& cardsA, const cards& cardsB)
{
  if (K == 0)
    return (cardsA == cardsB) ? "YES" : "NO";
  if (K == 1 && cardsA == cardsB)
    return "NO";
  int N = cardsA.size();      // No. cards
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
  for (size_t t = 1; t <= T; t++) {
    int N;            // No. cards N: 2 ≤ N ≤ 500,000
    int K;            // No. swaps K: 0 ≤ K ≤ 10e9
    cin >> N >> K;
    cards cardsA = inputCards(N);
    cards cardsB = inputCards(N);
    cout << "Case #" << t << ": " << solve(K, cardsA, cardsB) << endl;
  }
  return 0;
}
