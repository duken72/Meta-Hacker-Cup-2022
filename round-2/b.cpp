#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>

using namespace std;
using LL = long long;
const LL MOD = 1'000'000'007;

// Addition and subtraction with modulo
template <typename T>
T add(const T& a, const T& b) { return (a % MOD + b % MOD) % MOD; }

struct Client {
  LL d1, d2;  // Buy and sell days
  LL c1, c2;  // Buy and sell prices
};

struct Node {
  int id;
  vector<pair<int, LL>> edges;
};

struct Graph {
  /* data */
};

LL solve()
{
  int N; cin >> N;          // No. of clients N: 1 ≤ N ≤ 10^6
  int K; cin >> K;          // No. of paths K: 1 ≤ K ≤ 10^6
  vector<Client> nodes(N);  // List of clients' info
  for (size_t i = 0; i < N; i++) {
    cin >> nodes[i].d1;
    cin >> nodes[i].d2;
    cin >> nodes[i].c1;
    cin >> nodes[i].c2;
  }

  return 0;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;      // No. test case T: 1 ≤ T ≤ 35
  for (size_t t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve() << endl;
  return 0;
}
