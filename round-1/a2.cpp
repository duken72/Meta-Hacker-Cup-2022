#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
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

void getCardMinCount(const cards& cardsIn, int& cardMin, int& countMin)
{
    cards uniqueCards(cardsIn);             // Unique cards
    sort(uniqueCards.begin(), uniqueCards.end());
    uniqueCards.erase(unique(uniqueCards.begin(), uniqueCards.end()),
                                        uniqueCards.end());
    countMin = cardsIn.size();             // Assume current max count
    int uniqueCount;
    for (auto uniqueCard : uniqueCards) {
        uniqueCount = count(cardsIn.begin(), cardsIn.end(), uniqueCard);
        if (countMin > uniqueCount) {
            cardMin = uniqueCard;
            countMin = uniqueCount;
        }
        if (countMin == 1) break;
    }
}

// Return the new card sequence after a swap
cards swapCards(const cards& cardsIn, const int& position)
{
    cards cardsOut(cardsIn.begin() + position, cardsIn.end());
    cardsOut.insert(cardsOut.end(), cardsIn.begin(), cardsIn.begin() + position);
    return cardsOut;
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

    // Find the card with minimum no. counts
    int cardMin, countMin;
    getCardMinCount(cardsA, cardMin, countMin);
    if (K == 1 && N == 3 && countMin == 1 && cardsA == cardsB)
        return "NO";
    if (N == countMin)          // All the cards are the same
        return "YES";

    // Try all possible swaps
    int cardMinIndA = find(cardsA.begin(), cardsA.end(), cardMin) - cardsA.begin();
    int cardMinIndB;            // The ind of the cardMin in B
    cards cardsC;               // A card sequence after swap
    auto itB = cardsB.begin();  // Iterator over sequence B
    for (int i = 0, c; i < countMin; i++) {
        cardMinIndB = find(itB, cardsB.end(), cardMin) - cardsB.begin();
        c = cardMinIndA - cardMinIndB;
        cardsC = (c > 0) ? swapCards(cardsA, c) : swapCards(cardsA, c+N);
        if (cardsC == cardsB)
            return "YES";
        itB++;
    }
    return "NO";
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

// Time = 3.2[s]
