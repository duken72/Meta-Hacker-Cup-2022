// Naive approach, O(N*Q), not working :)

#include <iostream>
#include <vector>

using namespace std;

using LL = long long;

string solve()
{
    int N, M, Q;            // No. nodes N, edges M, queries Q
    cin >> N >> M >> Q;     // 1 ≤ N, M, Q ≤ 2e5
    vector<vector<LL>> C(N, vector(N, (LL)0));  // matrix C(N x N)
    for (int m = 0, Ai, Bi; m < M; m++) {
        cin >> Ai >> Bi;        // Indices: 1 ≤ Ai, Bi ≤ N
        cin >> C[--Ai][--Bi];   // No. guest/flight Ci: 1 ≤ Ci ≤ 10e9
        C[Bi][Ai] = C[Ai][Bi];
    }
    string result;
    for (int q = 0, Xi, Yi; q < Q; q++) {
        cin >> Xi >> Yi;        // Indices: 1 ≤ Xi, Yi ≤ N
        LL Fi = 2 * C[--Xi][--Yi];
        for (size_t i = 0; i < N; i++) {
            if (i == Yi)
                continue;
            if (C[Xi][i] != 0 && C[i][Yi] != 0)
                Fi += min(C[Xi][i], C[i][Yi]);
        }
        result += " " + to_string(Fi);
    }
    result += "\n";
    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;          // No. test cases T: 1 ≤ T ≤ 70
    for (size_t t = 1; t <= T; t++)
        cout << "Case #" << t << ":" << solve();
    return 0;
}
