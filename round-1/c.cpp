#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
using LL = long long;
using Coord = std::pair<LL, LL>;
#define x first
#define y second

const LL MAX = LLONG_MAX;

LL sqrDist(const Coord &a, const Coord &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

LL cross(const Coord &a, const Coord &b, const Coord &o = Coord(0, 0)) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

struct sortDistance {
    Coord ref1_, ref2_;
    sortDistance(const Coord& p1, const Coord& p2) : ref1_(p1), ref2_(p2) {}

    bool operator() (const Coord& p1, const Coord& p2) {
        if (sqrDist(p1, ref1_) == sqrDist(p2, ref1_))
            return sqrDist(p1, ref2_) > sqrDist(p2, ref2_); 
        return sqrDist(p1, ref1_) < sqrDist(p2, ref1_);
    }
};

template <class It>
vector<Coord> convex_hull(It lo, It hi) {
    int k = 0;
    if (hi - lo <= 1)
        return vector<Coord>(lo, hi);
    vector<Coord> res(2 * distance(lo, hi));
    sort(lo, hi);
    for (It it = lo; it != hi; ++it) {
        while (k >= 2 && cross(res[k - 1], *it, res[k - 2]) >= 0)
            k--;
        res[k++] = *it;
    }
    int t = k + 1;
    for (It it = hi - 2; it != lo - 1; --it) {
        while (k >= t && cross(res[k - 1], *it, res[k - 2]) >= 0)
            k--;
        res[k++] = *it;
    }
    res.resize(k - 1);
    return res;
}

#define LOG             true
#define PRIORITY_QUEUE  true
LL solve()
{
    int N;                      // No. houses N: 2 ≤ N ≤ 1e6
    LL K, D, D2;                // Distances K, D: 0 ≤ K, D ≤ 1e9
    cin >> N >> K >> D;
    D2 = D * D;
    vector<Coord> houses(N);    // Vector of house coordinates
    for (int n = 0; n < N; n++)
        cin >> houses[n].x >> houses[n].y;

    Coord base = houses[0], target = houses[N-1];
    vector<Coord> convexPts = convex_hull(houses.begin(), houses.end());

#if PRIORITY_QUEUE  // with priority queue
    convexPts.erase(find(convexPts.begin(), convexPts.end(), target));
    convexPts.push_back(target);
#else               // without priority queue
    sort(convexPts.begin(), convexPts.end(), sortDistance(base, target));
    auto itTarget = find(convexPts.begin(), convexPts.end(), target);
    // Ignore points that is further than the target point
    convexPts.erase(itTarget + 1, convexPts.end());
#endif

    N = convexPts.size();
    LL d = sqrDist(base, target);
    if (N == 2)                 // Edge case N == 2
        return (d <= D2) ? max(K, d) : -1;

    // Dijkstra algorithm
    vector<LL> costs(N, MAX); costs[0] = 0;     // Init distances
    Coord src, dest;
    for (size_t i = 1; i < N; i++) {
        d = sqrDist(base, convexPts[i]);
        if (d > D2)
            continue;
        costs[i] = max(K, d);
    }
#if PRIORITY_QUEUE  // with priority queue. Time = 2m 14s
    vector<int> unvisited;
    for (size_t i = 1; i < N; i++)
        unvisited.push_back(i);
    while (true) {
#if LOG
        cout << "Total points: " << N-2 << " Iter: " << N-2-unvisited.size() << endl;
#endif
        int indSrc = -1;
        LL minDist = MAX;
        for (int i : unvisited) {
            indSrc = (minDist > costs[i]) ? i : indSrc;
            minDist = min(minDist, costs[i]);
        }        
        if (minDist == MAX || indSrc == N-1)
            break;
        unvisited.erase(find(unvisited.begin(), unvisited.end(), indSrc));
        for (int indEnd : unvisited) {
            d = sqrDist(convexPts[indSrc], convexPts[indEnd]);
            if (d > D2) continue;
            LL newCost = costs[indSrc] + max(K, d);
            costs[indEnd] = min(newCost, costs[indEnd]);
        }
    }
#else               // without priority queue. Time = 42[s]
    for (size_t indSrc = 1; indSrc < N-1; indSrc++) {
#if LOG
        cout << "Total points: " << N-2 << " Iter: " << indSrc << endl;
#endif
        if (costs[indSrc] == MAX) continue;
        src = convexPts[indSrc];         // Start point
        for (size_t indEnd = indSrc+1; indEnd < N; indEnd++) {
            d = sqrDist(src, convexPts[indEnd]);
            if (d > D2) continue;
            LL newCost = costs[indSrc] + max(K, d);
            costs[indEnd] = min(newCost, costs[indEnd]);
        }
    }
#endif
    return (costs[N-1] < MAX) ? costs[N-1] : -1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;        // No. test cases T: 1 ≤ T ≤ 90
    for (size_t t = 1; t <= T; t++)
        cout << "Case #" << t << ": " << solve() << endl;
    return 0;
}
