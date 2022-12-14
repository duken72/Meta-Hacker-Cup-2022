#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <algorithm>

#define card first
#define teamA second

using namespace std;
using Cards = vector<int>;

Cards readCards(int numCard)
{
    Cards cards(numCard);
    for (int n = 0; n < numCard; n++)
        cin >> cards[n];
    sort(cards.begin(), cards.end(), greater<int>());
    return cards;
}

bool sortCard(const pair<int, bool>& v1, const pair<int, bool>& v2) {
    return v1.first > v2.first;
}

int solve()
{
    int N; cin >> N; N = N/4;       // No. cards
    Cards A1 = readCards(N);        // Player A1 cards
    Cards B1 = readCards(N);        // Player B1 cards
    Cards A2 = readCards(N);        // Player A2 cards
    Cards B2 = readCards(N);        // Player B2 cards    
    // Vector of the highest cards and if it's from team A
    vector<pair<int, bool>> bestCards(N);
    for (size_t i = 0; i < N; i++)
        bestCards[i] = pair<int, bool>(A1[i], true);    // A1 turns
    // Vect of indices for faster iteration
    vector<int> idTeamA, idTeamB;

    // B1 covers as many as possible cards of A1
    for (size_t i = 0; i < N; i++) {
        if (B1[0] < bestCards[i].card) {
            idTeamA.push_back(i);
            continue;
        }
        bestCards[i] = pair<int, bool>(B1[0], false);
        B1.erase(B1.begin());
        idTeamB.push_back(i);
    }
    reverse(idTeamA.begin(), idTeamA.end());

    // A2 covers as many as possible cards of B1
    for (int idB : idTeamB) {
        if (A2[0] < bestCards[idB].card) continue;
        bestCards[idB] = pair<int, bool>(A2[0], true);
        A2.erase(A2.begin());
    }
    // A2 covers as many as possible lowest cards of A1
    for (int idA : idTeamA) {
        if (A2[0] < bestCards[idA].card) continue;
        bestCards[idA].card = A2[0];
        A2.erase(A2.begin());
    }
    sort(bestCards.begin(), bestCards.end(), sortCard);

    // B2 covers as many as possible cards of team A
    for (size_t i = 0; i < N; i++) {
        if (bestCards[i].teamA != true) continue;
        if (B2[0] < bestCards[i].card) continue;
        bestCards[i] = pair<int, bool>(B2[0], false);
        B2.erase(B2.begin());
    }
    int points = 0;
    for (size_t i = 0; i < N; i++)
        points += bestCards[i].teamA;
    return points;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;        // No. test case T: 1 ≤ T ≤ 500
    for (size_t t = 1; t <= T; t++)
        cout << "Case #" << t << ": " << solve() << endl;
    return 0;
}
// Time t = 4[min]
