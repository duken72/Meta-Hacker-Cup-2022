// Faster than d2, but still slow due to using vector??
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
using LL = long long;

struct Node {
  vector<pair<int, LL>> edges;
};
void solve()
{
  // No. airports N, flight paths M, days Q: 1 ≤ N, M, Q ≤ 2e5
  int N, M, Q; cin >> N >> M >> Q;
  vector<Node> nodes(N);
  LL Ci;                    // No. guest/flight Ci: 1 ≤ Ci ≤ 10e9
  for (int m = 0, Ai, Bi; m < M; m++) {
    cin >> Ai >> Bi >> Ci;  // Indices: 1 ≤ Ai, Bi ≤ N
    Ai--; Bi--;
    nodes[Ai].edges.push_back(pair<int, LL>(Bi, Ci));
    nodes[Bi].edges.push_back(pair<int, LL>(Ai, Ci));
  }
  // Find "big" nodes, more than root_M edges
  float root_M = sqrt(M);
  vector<int> big_nodes;
  for (size_t i = 0; i < N; i++) {
    if (nodes[i].edges.size() > root_M)
      big_nodes.push_back(i);
  }
  int no_big_nodes = big_nodes.size();
  vector<vector<LL>> pre_dist(no_big_nodes, vector<LL>(N, 0));
  for (int i = 0; i < no_big_nodes; i++) {
    int id_big = big_nodes[i];
    for (auto [id_mid, val_mid] : nodes[id_big].edges) {
      for (auto [id_end, val_end] : nodes[id_mid].edges) {
        pre_dist[i][id_end] += min(val_mid, val_end);
      }
    }
  }
  
  for (int q = 0, Xi, Yi; q < Q; q++) {
    cin >> Xi >> Yi; Xi--; Yi--;    // Indices: 1 ≤ Xi, Yi ≤ N
    if (nodes[Xi].edges.size() < nodes[Yi].edges.size())
      swap(Xi, Yi);                 // Yi has less edges than Xi
    LL Fi = 0;
    // The direct cost
    for (auto [id, val] : nodes[Yi].edges) {
      if (id == Xi) {
        Fi = 2 * val;
        break;
      }      
    }
    // The indirect cost
    auto itXi = find(big_nodes.begin(), big_nodes.end(), Xi); 
    if (itXi != big_nodes.end()) {    // If there is a big node
      Fi += pre_dist[itXi - big_nodes.begin()][Yi];
    } else {                          // Both are small nodes
      vector<LL> cost_from_Xi(N, 0), cost_from_Yi(N, 0);
      for (auto [id, val] : nodes[Xi].edges)
        cost_from_Xi[id] = val;
      for (auto [id, val] : nodes[Yi].edges)
        cost_from_Yi[id] = val;
      for (size_t i = 0; i < N; i++)
        Fi += min(cost_from_Xi[i], cost_from_Yi[i]);
    }
    cout << " " << Fi;
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;          // No. test cases T: 1 ≤ T ≤ 70
  T = 3;
  for (size_t t = 1; t <= T; t++) {
    cout << "Case #" << t << ":";
    solve();
    cout << endl;
  }
  return 0;
}
// Time t = ?[s]