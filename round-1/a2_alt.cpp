#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using cards = vector<int>;

cards inputCards(const int& N)
{
    vector<int> output(N);
    for (size_t i = 0; i < N; i++)
        cin >> output[i];     // Card's values: 1 ≤ Ai, Bi ≤ 10e9
    return output;
}

string card2str(const cards& cardsIn)
{
    std::stringstream ss;
    for (auto card : cardsIn)
        ss << card << " ";
    return ss.str();
}

string solve()
{
    int N, K;                   // No. cards N, cuts K
    cin >> N >> K;              // 2 ≤ N ≤ 500,000, 0 ≤ K ≤ 10e9
    cards cardsA = inputCards(N);
    cards cardsB = inputCards(N);

    if (K == 0)                 // Edge case: no cut
        return (cardsA == cardsB) ? "YES" : "NO";
    if (N == 2) {               // Edge case: only 2 cards
        if (K%2 == 1)           // With odd K, the order reverses
           reverse(cardsA.begin(), cardsA.end());
        return (cardsA == cardsB) ? "YES" : "NO";
    }

    string A = card2str(cards(cardsA.begin()+1, cardsA.end()));
    string B = card2str(cards(cardsB.begin(), cardsB.end()-1));
    string C = A + B;
    // Naive substring search
    return (C.find(B) != string::npos) ? "YES" : "NO";
    // Consider other linear time string-matching techniques
    // e.g.: the Knuth-Morris-Pratt, Boyer-Moore, or Z algorithm
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;        // No. cases T: 1 ≤ T ≤ 205    
    for (size_t t = 1; t <= T; t++)        
        cout << "Case #" << t << ": " << solve() << endl;
    return 0;
}

// Time = 2m 1s, and .. incorrect?
