#include <iostream>
#include <vector>

using std::cout, std::cin, std::endl;
using std::vector, std::string, std::min;

void solve(const int& Q, const vector<vector<int>>& C)
{
  int Xi, Yi;     // Indices: 1 ≤ Xi, Yi ≤ N
  int N = C.size();
  for (size_t q = 0; q < Q; q++) {
    cin >> Xi >> Yi; Xi--; Yi--;
    int Fi = 0;
    Fi += 2 * C[Xi][Yi];
    for (size_t i = 0; i < N; i++) {
      if (i == Yi) continue;
      if (C[Xi][i] != 0) {
        if (C[i][Yi] != 0)
          Fi += min(C[Xi][i], C[i][Yi]);
      }
    }
    cout << " " << Fi;
  }
  cout << endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T; cin >> T;// No. test cases T:    1 ≤ T ≤ 70
  int N, M, Q;    // No. airports N, flight paths M, days Q: 1 ≤ N,M,Q ≤ 2e5
  int Ai, Bi;     // Indices: 1 ≤ Ai, Bi ≤ N
  int Ci;         // No. guest per flight Ci: 1 ≤ Ci ≤ 10e9
  for (size_t t = 1; t <= T; t++) {
    cout << "Case #" << t << ":";
    cin >> N >> M >> Q;
    vector<vector<int>> C(N, vector(N, 0));   // matrix C(N x N)
    for (size_t m = 0; m < M; m++) {
      cin >> Ai >> Bi >> Ci; Ai--; Bi--;
      C[Ai][Bi] = Ci;
      C[Bi][Ai] = Ci;
    }
    solve(Q, C);
  }
  return 0;
}
