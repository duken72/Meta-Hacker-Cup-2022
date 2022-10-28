#include <iostream>
#include <vector>

using std::cout, std::cin, std::endl, std::vector;
using LL = long long;
using vectLL = vector<LL>;

// Least Significant Bit (id & ~(id-1) also works)
inline int LSB(int id) { return id & -id; }
struct FenwickTree
{
  vectLL A, T;          // Original array A and the tree T
  FenwickTree(int N) : A(N + 1), T(N + 1) {}
  LL query(int id) const
  {
    LL sum = 0;
    for (; id > 0; id -= LSB(id))
      sum += T[id];
    return sum;
  }
  // Update by increment
  void update(int id, LL val)
  {
    A[id] += val;
    int N = T.size();
    for (; id < N; id += LSB(id))
      T[id] += val;
  }
  LL at(int id) const { return A[id]; } // Get array value at id
  LL query(int low, int high) const { return query(high) - query(low - 1); }
  // Update by setting
  void set(int id, LL val) { update(id, val - A[id]); }
};

template <typename Predicate>
int binary_search(int lowInd, int highInd, Predicate pred) {
  int midInd;
  while (lowInd < highInd) {
    midInd = lowInd + (highInd - lowInd + 1) / 2;
    if (pred(midInd)) {
      lowInd = midInd;
    } else {
      highInd = midInd - 1;
    }
  }
  return pred(lowInd) ? lowInd : highInd+1;
}

LL getNumSwap(const FenwickTree &C1, const FenwickTree &C2,
  const FenwickTree &I1, const FenwickTree &I2, const int &Zi)
{
  int N = C1.A.size() - 1;      // Total No. tasks
  int N2 = C1.query(N);         // No. task 2
  int N1 = N - N2;              // No. task 1
  int sum = (N1 + 2 * N2) / 2;  // half the sum of all task time
  float avg = (float)sum / Zi;  // average time for Zi tasks
  if ((N1 % 2) ||               // Odd no. task 1
      (avg < 1 || avg > 2) ||   // Out of range average
      (avg == 1 && N1 < Zi) ||  // Minimum average
      (avg == 2 && N2 < Zi))    // Maximum average
    return -1;
  int L, H;         // No. task 2 in Lower and Higher sides
  int d;            // 1/2 of sum difference, = no. tasks to move
  L = C1.query(Zi); // currently left side
  int sumLeft = (Zi - L) + 2 * L;
  // Variables for the suitable trees
  const FenwickTree *C, *I; int Z;
  if (sumLeft == sum)
    return 0;
  else if (sumLeft < sum) {
    d = sum - sumLeft;
    Z = Zi; C = &C1; I = &I1;
  } else if (sumLeft > sum) {
    d = sumLeft - sum;
    L = N2 - L;
    Z = N - Zi; C = &C2; I = &I2;
  }
  if ((N2 - L < d) ||   // Edge case: not enough 2 from higher side
      (Z - L < d))      // Edge case: not enough 1 from lower side
    return -1;  
  // The id from which the subarray will be filled with 2s
  int s = binary_search(1, Z, [&](int s)
    { return (*C).query(s-1) + (Z - s + 1) >= L+d; });
  int S1 = (*C).query(s - 1);
  // The id of the last 2 will be moved
  int t = binary_search(s, N, [&](int t)
    { return (*C).query(t) - S1 <= (Z - s + 1); });
  if (s > Z || t > N)
    return -1;
  return (*I).query(s, t) - (LL)(Z-s+1) * (s+Z) / 2;
}

LL solve()
{
  int N; cin >> N;          // No. tasks N:   1 ≤ N ≤ 1e6
  int M; cin >> M;          // No. updates M: 1 ≤ M ≤ 1e6
  auto rev = [=](int id) -> int
    { return N - id + 1; }; // Reverse lambda function
  FenwickTree C1(N), C2(N), I1(N), I2(N);
  for (int n = 1, Ai; n <= N; n++) {
    cin >> Ai;              // Task time Ai ∈ {1,2}
    C1.set(n, Ai == 2);
    I1.set(n, (Ai == 2) ? n : 0);
    C2.set(rev(n), Ai == 2);
    I2.set(rev(n), (Ai == 2) ? rev(n) : 0);
  }
  LL Q = 0;                 // No. swaps Q
  // Indices Xi, Zi: 1 ≤ Xi, Zi ≤ N, task time Yi ∈ {1,2}
  for (int m = 1, Xi, Yi, Zi; m <= M; m++) {
    cin >> Xi >> Yi >> Zi;
    C1.set(Xi, Yi == 2);
    I1.set(Xi, (Yi == 2) ? Xi : 0);
    C2.set(rev(Xi), Yi == 2);
    I2.set(rev(Xi), (Yi == 2) ? rev(Xi) : 0);
    Q += getNumSwap(C1, C2, I1, I2, Zi);
  }
  return Q;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;      // No. test case T: 1 ≤ T ≤ 95
  for (size_t t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve() << endl;
  return 0;
}
// Time = 20-23[s]