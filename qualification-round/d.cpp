// Based on given solution
#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <cmath>
#include <unordered_map>
using namespace std;

using LL = long long;
const int LIM = 200000;
unordered_map<int, int> adj[LIM];     // Adjacency matrix (kind of)
unordered_map<int, LL> pre_dist[LIM]; // Precomputed costs for big nodes

void clear_map() {
  for (size_t i = 0; i < LIM; i++) {
    adj[i].clear();
    pre_dist[i].clear();
  }
}
inline int degree(int i) { return adj[i].size(); }

void solve()
{
  clear_map();
  // No. nodes N, edges M, queries Q: 1 ≤ N, M, Q ≤ 2e5
  int N, M, Q; cin >> N >> M >> Q;
  LL Ci;                    // No. guest/flight Ci: 1 ≤ Ci ≤ 10e9
  for (int m = 0, Ai, Bi; m < M; m++) {
    cin >> Ai >> Bi >> Ci;  // Indices: 1 ≤ Ai, Bi ≤ N
    Ai--; Bi--;
    adj[Ai][Bi] = adj[Bi][Ai] = Ci;
  }
  // Precomputed distance from big nodes (with more than root_M edges)
  int root_M = sqrt(M);
  for (size_t u = 0; u < N; u++) {
    if (degree(u) < root_M) continue;   // Small nodes
    for (auto const &[mid, cost1] : adj[u]) {
      for (auto const &[v, cost2] : adj[mid])
        pre_dist[u][v] += min(cost1, cost2);
    }
  }
  // Query
  for (int q = 0, Xi, Yi; q < Q; q++) {
    cin >> Xi >> Yi; Xi--; Yi--;    // Indices: 1 ≤ Xi, Yi ≤ N
    LL Fi = 0;
    if (degree(Xi) < degree(Yi))
      swap(Xi, Yi);                 // Yi has less edges than Xi
    if (adj[Yi].count(Xi))
      Fi += 2 * adj[Yi][Xi];        // Direct cost
    if (degree(Xi) > root_M) {  // Xi is a big node
      Fi += pre_dist[Xi][Yi];
    } else {                        // Two small nodes
      for (auto const &[mid, cost] : adj[Xi]) {
        if (adj[mid].count(Yi))
          Fi += min(cost, adj[mid][Yi]);
      }
    }
    cout << " " << Fi;
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;          // No. test cases T: 1 ≤ T ≤ 70
  for (size_t t = 1; t <= T; t++) {
    cout << "Case #" << t << ":";
    solve();
    cout << endl;
  }
  return 0;
}
// Time t = 1m 12s