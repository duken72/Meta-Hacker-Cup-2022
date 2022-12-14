#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int S = 100;

#define USE_ARRAY true
string solve()
{
    int N, K;                   // No. parts N, case capacity K
    cin >> N >> K;              // 1 ≤ N ≤ 100, 1 ≤ K ≤ 100
#if USE_ARRAY   // using array
    int partCounts[S] = {0};    // Array of counts of each part type
    for (int n = 0, Si; n < N; n++) {
        cin >> Si; Si--;        // Part index Si: 1 ≤ Si ≤ 100
        partCounts[Si]++;       // Count increment
    }
#else           // using vector
    vector<int> vectPart(N);    // Input part indices
    for (int n = 0; n < N; n++)
        cin >> vectPart[n];     // Part index Si: 1 ≤ Si ≤ 100
#endif

    if (N > 2 * K)              // Criterion 1: N < 2K
        return "NO";

#if USE_ARRAY   // using array, slightly faster. Time t = 3[ms]
    int maxCount = 0;
    for (int val : partCounts) {
        maxCount = max(maxCount, val);
        if (maxCount > 2)       // Criterion 2: no more than 2 same items
            return "NO";
    }    
#else           // Using vector, slightly slower. Time t = 7[ms]
    std::vector<int> partCounts(S+1);   // Counts of each part type
    for (size_t s = 0; s <= S; s++)
        partCounts[s] = count(vectPart.begin(), vectPart.end(), s);
    int maxCount = *max_element(partCounts.begin(), partCounts.end());
    if (maxCount > 2)           // Criterion 2: no more than 2 same items
        return "NO";
#endif
    return "YES";
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;                // No. test case T: 1 ≤ T ≤ 90
    for (int t = 1, N, K; t <= T; t++)
        cout << "Case #" << t << ": " << solve() << endl;
    return 0;
}
