#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>
#include <math.h>

using namespace std;

// Return N codewords of length L
vector<string> GetCodewords(const int N, const int L)
{
    std::vector<std::string> codeWords;
    for (size_t i = 0; i < N; i++) {
        string binaryString = bitset<200>(i).to_string();
        replace(binaryString.begin(), binaryString.end(), '0', '.');
        replace(binaryString.begin(), binaryString.end(), '1', '-');
        codeWords.push_back(binaryString.substr(200-L, L));
    }
    return codeWords;
}

void solve()
{
    int N;                  // No. codewords N: 2 ≤ N ≤ 100
    string C1;              // 1st codeword
    cin >> N >> C1;

    int L = ceil(log2(N));  // The length for enough codewords
    vector<string> codewords = GetCodewords(N-1, L);
    string startChar = (C1[0] == '.') ? "-" : ".";
    for (auto word : codewords)
        cout << startChar + word << endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;          // No. test cases T: 1 ≤ T ≤ 100
    for (size_t t = 1; t <= T; t++) {
        cout << "Case #" << t << ":" << endl;
        solve();
    }
    return 0;
}

// Time t = 50[ms]
