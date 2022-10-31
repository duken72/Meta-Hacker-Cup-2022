#include <iostream>
#include <vector>

using std::cout, std::cin, std::endl;
using LL = long long;

// Modular Arithmetic
const LL MOD = 1000000007;
template <typename T>
T subMod(const T& a, const T& b) { return ((a - b)%MOD + MOD)%MOD; }
template <typename T>
T mulMod(const T& a, const T& b) { return (a * b)%MOD; }

// Find GCD of two numbers (greatest common divisor)
template <typename T>
T findGCD(const T& a, const T& b) {
  if (b == 0) return a;
  return findGCD(b, a%b);
}
template <typename T>
T gcdExtended(T a, T b, T* x, T* y) { 
  if (a == 0) {
    *x = 0, *y = 1;
    return b;
  }
  T x1, y1;
  T gcd = gcdExtended(b % a, a, &x1, &y1);
  *x = y1 - (b / a) * x1;
  *y = x1;
  return gcd;
}
// Simplify a fraction
template <typename T>
void lowestFraction(T& num, T& denom) {
  T GCD = findGCD(num, denom);
  num /= GCD;
  denom /= GCD;
}
// Mod Inverse
// geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
LL modInverse(LL A) {
  LL x, y, out;
  LL g = gcdExtended(A, MOD, &x, &y);
  out = (x % MOD + MOD) % MOD;
  return out;
}

template <typename T>
void getCombinatorial(const LL& N, const LL& K,
  const std::vector<LL>& FACTORIAL_MOD, T& num, T& denom)
{
  if (N < K) {
    num = 0;
    denom = 1;
    return;
  } else if (N == K) {
    num = 1;
    denom = 1;
    return;
  }  
  num = FACTORIAL_MOD[N-1];
  denom = mulMod(FACTORIAL_MOD[N-K-1], FACTORIAL_MOD[K-1]);
  lowestFraction(num, denom);
}

// Find Prob of getting a chocolate cookies
LL getProb(const LL& C1, const LL& C2, const LL& C3, const LL& C4,
  const std::vector<LL>& FACTORIAL_MOD, const LL& K)
{
  LL C = C1 + C2 + C3 + C4;       // Total no. cookies
  if (K + 1 > C - C4)             // Edge case: K+1 > C1 + C2 + C3
    return 0;  
  LL x, y;    // Final prob of getting chocolate cookies: x/y
  LL x1, y1;  // No. ways to pick K+1 from (C1+C2+C3)=(C-C4): x1/y1
  getCombinatorial(C - C4, K+1, FACTORIAL_MOD, x1, y1);
  LL x2, y2;  // No. ways to pick K+1 from C2: x2/y2
  getCombinatorial(C2, K+1, FACTORIAL_MOD, x2, y2);
  LL x3, y3;  // No. ways to pick K+1 from C: x3/y3
  getCombinatorial(C, K+1, FACTORIAL_MOD, x3, y3);
  // No. ways to pick at least 1 cookies of W1: x/y = x1/y1 - x2/y2
  x = subMod(mulMod(x1, y2), mulMod(x2, y1));
  y = mulMod(y1, y2);
  lowestFraction(x, y);
  // Prob of picking at least 1 cookies of W1: (x/y) / (x3/y3)
  x = mulMod(x, y3);
  y = mulMod(y, x3);
  lowestFraction(x, y);
  if (C3 != 0) {    // Tie breaking prob, due to same weights
    x = mulMod(x, C1);
    y = mulMod(y, C1+C3);
    lowestFraction(x, y);
  }
  return mulMod(x, modInverse(y));
}

LL solve(const std::vector<LL>& FACTORIAL_MOD)
{
  int N; cin >> N;  // No. of batches N: 2 ≤ N ≤ 3000
  LL K; cin >> K;   // No. of times weighting K: 1 ≤ K ≤ 9e6
  // No. of cookies from batch 1: C1, lighter than batch 1: C2
  // equal to batch 1: C3, heavier than batch 1: C4, 1 ≤ Ci ≤ 3000
  LL C1, C2 = 0, C3 = 0, C4 = 0; cin >> C1;
  LL W1; cin >> W1;     // weight Wi: 1 ≤ Ci ≤ 1e9
  for (LL n = 1, Ci, Wi; n < N; n++) {
    cin >> Ci >> Wi;
    if (Wi < W1)
      C2 += Ci;
    else if (Wi == W1)
      C3 += Ci;
    else
      C4 += Ci;
  }
  return getProb(C1, C2, C3, C4, FACTORIAL_MOD, K);
}
int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T; cin >> T;    // No. test case T: 1 ≤ T ≤ 1000
  // Pre-create an array of the mod of factorial from 1 to 9e6
  std::vector<LL> FACTORIAL_MOD(9000000, 1);
  for (LL i = 1; i < 9000000; i++)
    FACTORIAL_MOD[i] = mulMod(FACTORIAL_MOD[i-1], i+1);
  for (size_t t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve(FACTORIAL_MOD) << endl;
  return 0;
}
// Time = 1-2[s]