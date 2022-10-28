#include <iostream>
#include <vector>
#include <algorithm>  // std::sort
#include <utility>    // std::pair
const int DEBUG_LEVEL = 0;
#include "log.hpp"
#define card first
#define teamA second

using std::cout, std::cin, std::endl;
using std::vector, std::sort, std::greater, std::pair;
using Cards = vector<int>;

Cards readCards(int numCard)
{
  Cards cards(numCard);
  for (int n = 0; n < numCard; n++)
    cin >> cards[n];
  sort(cards.begin(), cards.end(), greater<int>());
  return cards;
}
bool sortCard(const pair<int, bool>& v1, const pair<int, bool>& v2) {
  return v1.first > v2.first;
}

int solve()
{
  int N; cin >> N; N = N/4;   // No. cards
  Cards A1 = readCards(N);    // Player A1 cards
  Cards B1 = readCards(N);    // Player B1 cards
  Cards A2 = readCards(N);    // Player A2 cards
  Cards B2 = readCards(N);    // Player B2 cards
  
  // Vector of the highest cards and if it's from team A
  vector<pair<int, bool>> bestCards(N, pair<int, bool>(0, true));
  for (size_t i = 0; i < N; i++)
    bestCards[i].card = A1[i];    // A1 turns
  // B1 covers as many as possible cards of A1
  for (size_t i = 0; i < N; i++) {
    if (B1[0] > bestCards[i].card) {
      bestCards[i].card = B1[0];
      bestCards[i].teamA = false;
      B1.erase(B1.begin());
    }    
  }
  // Vect of indices for faster iteration
  vector<int> idTeamA, idTeamB;
  for (size_t i = 0; i < N; i++) {
    if (bestCards[i].teamA)
      idTeamA.insert(idTeamA.begin(), i);
    else
      idTeamB.push_back(i);
  }
  // A2 covers as many as possible cards of B1
  for (int idB : idTeamB) {
    if (A2[0] > bestCards[idB].card) {
      bestCards[idB].card = A2[0];
      bestCards[idB].teamA = true;
      A2.erase(A2.begin());
    }
  }
  // A2 covers as many as possible lowest cards of A1
  for (int idA : idTeamA) {
    if (A2[0] > bestCards[idA].card) {
      bestCards[idA].card = A2[0];
      A2.erase(A2.begin());
    }
  }
  sort(bestCards.begin(), bestCards.end(), sortCard);
  // B2 covers as many as possible cards of team A
  for (size_t i = 0; i < N; i++) {
    if (B2[0] > bestCards[i].card && bestCards[i].teamA == true) {
      bestCards[i].card = B2[0];
      bestCards[i].teamA = false;
      B2.erase(B2.begin());
    }
  }
  int points = 0;
  for (size_t i = 0; i < N; i++) {
    if (bestCards[i].teamA)
      points++;
  }
  return points;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  steady_clock::time_point t1 = steady_clock::now();
  int T; cin >> T;    // No. test case T: 1 ≤ T ≤ 500
  for (size_t t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve() << endl;
  steady_clock::time_point t2 = steady_clock::now();
  cout << "Using coordinates' sum in t = "
       << duration_cast<sec>(t2 - t1).count() << "[s]" << endl;
  return 0;
}
// Time = 3m32s