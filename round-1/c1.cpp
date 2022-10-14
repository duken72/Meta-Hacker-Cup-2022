#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>
#include <math.h>

using std::cout, std::cin, std::endl, std::vector, std::ostream;
using std::sort, std::max, std::pair, std::distance;
using LL = long long;
using Coord = std::pair<LL, LL>;
#define x first
#define y second
using std::chrono::steady_clock, std::chrono::duration_cast, std::chrono::seconds;

const LL MAX = LLONG_MAX;
const int DEBUG_LEVEL = 1;

// Supporting function for: printing and logging
template <class... Args>
void LOGIF(const int& level, Args... args) {
  if (level > DEBUG_LEVEL) return;
  (cout << ... << args) << "\n";
}

LL sqrDist(const Coord &a, const Coord &b) {
  return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
struct sortDistance {
  Coord ref1_, ref2_;
  sortDistance(const Coord& ref1, const Coord& ref2) { ref1_ = ref1; ref2_ = ref2; }
  bool operator() (const Coord& p1, const Coord& p2) {
    if (sqrDist(p1, ref1_) == sqrDist(p2, ref1_))
      return sqrDist(p1, ref2_) > sqrDist(p2, ref2_); 
    return sqrDist(p1, ref1_) < sqrDist(p2, ref1_);
  }
};
LL cross(const Coord &a, const Coord &b, const Coord &o = Coord(0, 0)) {
  return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}
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

LL solve()
{
  int N;                    // No. houses N: 2 ≤ N ≤ 1e6
  LL K, D, D2;              // Distances K, D: 0 ≤ K, D ≤ 1e9
  cin >> N >> K >> D; D2 = D * D;
  vector<Coord> houses(N);  // Vector of house coordinates
  for (size_t n = 0; n < N; n++)
    cin >> houses[n].x >> houses[n].y;
  Coord base = houses[0];
  Coord target = houses[N-1];
  vector<Coord> convexPts = convex_hull(houses.begin(), houses.end());
  sort(convexPts.begin(), convexPts.end(), sortDistance(base, target));
  auto itTarget = find(convexPts.begin(), convexPts.end(), target);
  // Ignore points that is further than the target point
  convexPts.erase(itTarget + 1, convexPts.end());

  N = convexPts.size();
  LL d = sqrDist(base, target);
  if (N == 2)               // Edge case N == 2
    return (d <= D2) ? max(K, d) : -1;

  // Dijkstra algorithm without priority queue
  // Faster, but got 1 case wrong
  // Time = 78[s]

  // Init distances
  vector<LL> costs(N, MAX); costs[0] = 0;
  Coord src, dest;
  for (size_t i = 1; i < N; i++) {
    // dest = convexPts[i];
    d = sqrDist(base, convexPts[i]);
    if (d > D2) continue;
    costs[i] = max(K, d);
  }

  for (size_t indSrc = 1; indSrc < N-1; indSrc++) {
    LOGIF(1, "Total points: ", N-2, " Iter: ", indSrc);
    if (costs[indSrc] == MAX) continue;
    src = convexPts[indSrc];     // Start point
    for (size_t indEnd = indSrc+1; indEnd < N; indEnd++) {
      // dest = convexPts[indEnd];  // End point
      d = sqrDist(src, convexPts[indEnd]);
      if (d > D2) continue;
      LL newCost = costs[indSrc] + max(K, d);
      if (newCost < costs[indEnd])
        costs[indEnd] = newCost;
    }
  }
  return (costs[N-1] < MAX) ? costs[N-1] : -1;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  steady_clock::time_point t1 = steady_clock::now();
  int T; cin >> T;    // No. test cases T: 1 ≤ T ≤ 90
  for (size_t t = 1; t <= T; t++) {
    cout << "Case #" << t << ": " << solve() << endl;
  }
  steady_clock::time_point t2 = steady_clock::now();
  cout << "Time = "
       << duration_cast<seconds>(t2 - t1).count() << "[s]" << endl;
  return 0;
}
