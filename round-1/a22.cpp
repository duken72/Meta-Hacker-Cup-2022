#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout, std::cin, std::endl;
using std::vector, std::string, std::find;
using std::sort, std::unique, std::count;
using cards = vector<int>;
const int MAX_CARD = 1000000000;

cards inputCards(const int& N)
{
  vector<int> output;
  int val=0;      // 1 ≤ Ai, Bi ≤ 10e9
  for (size_t i = 0; i < N; i++) {
    cin >> val;
    output.push_back(val);
  }
  return output;
}

string card2str(const cards& cardsIn)
{
  std::stringstream ss;
  for (auto card : cardsIn)
    ss << card << " ";
  return ss.str();
}

string solve(const int& K, const cards& cardsA, const cards& cardsB)
{
  if (K == 0)         // Edge case: no cut
    return (cardsA == cardsB) ? "YES" : "NO";
  int N = cardsA.size();      // No. cards
  if (N == 2) {       // Edge case: If there is only 2 cards
    cards cardsC{cardsA[1], cardsA[0]};
    if (K%2 == 1)     // With odd K, the order has to be the same as C
      return (cardsB == cardsC) ? "YES" : "NO";
    if (K%2 == 0)     // With even K, the order stays the same as A
      return (cardsA == cardsB) ? "YES" : "NO";
  }
  string A = card2str(cards(cardsA.begin()+1, cardsA.end()));
  string B = card2str(cards(cardsB.begin(), cardsB.end()-1));
  string C = A + B;
  return (C.find(B) != string::npos) ? "YES" : "NO";
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T; cin >> T;    // No. cases T: 1 ≤ T ≤ 205
  int N;              // No. cards N: 2 ≤ N ≤ 500,000
  int K;              // No. swaps K: 0 ≤ K ≤ 10e9
  for (size_t t = 1; t <= T; t++) {
    cin >> N >> K;
    cards cardsA = inputCards(N);
    cards cardsB = inputCards(N);
    cout << "Case #" << t << ": " << solve(K, cardsA, cardsB) << endl;
  }
  return 0;
}
