#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using LL = long long;
using vectLL = vector<LL>;

// Least Significant Bit (id & ~(id-1) also works)
template<typename T>
inline T LSB(const T& i) { return i & -i; }

struct FenwickTree {
  vector<LL> A, T;        // Original array A and the tree T
  FenwickTree(int N) : A(N + 1), T(N + 1) {}

  LL at(int id) const { return A[id]; }
  LL query(int id) const
  {
    LL sum = 0;
    for (; id > 0; id -= LSB(id))
      sum += T[id];
    return sum;
  }
  LL query(int low, int high) const { return query(high) - query(low - 1); }
  // Update by increment
  void update(int id, LL val)
  {
    A[id] += val;
    int N = T.size();
    for (; id < N; id += LSB(id))
      T[id] += val;
  }
  // Update by setting
  void set(int id, LL val) { update(id, val - A[id]); }
};

LL getNumSwap(const FenwickTree& A1, const FenwickTree& A2,
  const FenwickTree& A3, const int& Zi)
{
  int N = A1.A.size() - 1;          // Total no. tasks
  int C1 = A1.query(N);             // Total no. task 1
  int C2 = A2.query(N);             // Total no. task 2
  int C3 = A3.query(N);             // Total no. task 3
  if ((C1+C3)%2)                    // Edge case: the total sum is odd
    return -1;
  int sum = (C1 + 2*C2 + 3*C3) / 2; // Time sum for Zi tasks
  float avg = (float)sum / Zi;      // Average time for Zi tasks
  float avg2 = (float)sum / (N-Zi); // Average time for (N-Zi) tasks
  // Keep the counts of two side of the array
  int H1, H2, H3, L1, L2, L3;
  L1 = A1.query(Zi);
  L3 = A3.query(Zi);
  if (avg < 1 || avg > 3 || avg2 < 1 || avg2 > 3)
    return -1;                      // Out of range average
  else if (avg == 1)                // Edge case: minimum average
    return (Zi > C1) ? -1 : Zi - L1;
  else if (avg == 3)                // Edge case: maximum average
    return (Zi > C3) ? -1 : Zi - L3;
  L2 = A2.query(Zi);
  int sumLeft = L1 + 2*L2 + 3*L3;
  if (sumLeft == sum) {
    return 0;
  } else if (sumLeft > sum) {
    H1 = L1; L1 = C1 - H1;
    H2 = L2; L2 = C2 - H2;
    H3 = L3; L3 = C3 - H3;
  } else {  // sumLeft < sum
    H1 = C1 - L1;
    H2 = C2 - L2;
    H3 = C3 - L3;
  }
  // The difference d between higher and lower sides
  int d = (H1 + 2*H2 + 3*H3) - (L1 + 2*L2 + 3*L3);
  LL Qi = 0, k;
  // Switch 3 from higher side with 1 from lower side
  if (d > 2) {
    k = min({d/4, H3, L1});
    H3 -= k; H1 += k;
    L3 += k; L1 -= k;
    d -= 4*k; Qi += k;
  }
  // Switch 3 from higher side with 2 from lower side
  if (d > 2) {
    k = min({d/2, H3, L2});
    H3 -= k; H2 += k;
    L3 += k; L2 -= k;
    d -= 2*k; Qi += k;
  }
  // Switch 2 from higher side with 1 from lower side
  if (d > 2) {
    k = min({d/2, H2, L1});
    H2 -= k; H1 += k;
    L2 += k; L1 -= k;
    d -= 2*k; Qi += k;
  }
  if (d == 0)
    return Qi;
  if ((d == 2 && ((H3>0 && L2>0) || (H2>0 && L1>0))) ||
      (d ==-2 && ((H1>0 && L2>0) || (H2>0 && L3>0))))
    return Qi + 1;
  return -1;
}

LL solve()
{
  int N; cin >> N;      // No. tasks N: 2 ≤ N ≤ 1e6
  int M; cin >> M;      // No. updates M: 1 ≤ M ≤ 1e6
  // 3 Fenwick tree for counting no. tasks
  FenwickTree A1(N), A2(N), A3(N);
  for (int n = 1, Ai; n <= N; n++) {
    cin >> Ai;          // Task time Ai ∈ {1,2,3}
    A1.set(n, Ai == 1);
    A2.set(n, Ai == 2);
    A3.set(n, Ai == 3);
  }
  LL Q = 0;             // No. swaps Q: 1 ≤ Q ≤ 1e12
  // Index Xi, Zi: 1 ≤ Xi, Zi ≤ N, task time Yi ∈ {1,2,3}
  for (int m = 1, Xi, Yi, Zi; m <= M; m++) {
    // cout << "N=" << N << " m=" << m << "/" << M << endl;
    cin >> Xi >> Yi >> Zi;
    A1.set(Xi, Yi == 1);
    A2.set(Xi, Yi == 2);
    A3.set(Xi, Yi == 3);
    Q += getNumSwap(A1, A2, A3, Zi);
  }
  return Q;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;      // No. test case T: 1 ≤ T ≤ 100
  for (size_t t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve() << endl;
  return 0;
}
// Time = 7[s]