#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>

using namespace std;

int solve() {}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;        // No. test case T: 1 ≤ T ≤ ??
    for (size_t t = 1; t <= T; t++)
        cout << "Case #" << t << ": " << solve() << endl;
    return 0;
}
