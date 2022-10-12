#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using std::cout, std::cin, std::endl;
using std::string, std::vector;
using LL = long long;

// Modular Arithmetic
const LL MOD = 1000000007;
template <typename T>
T addMod(const T& a, const T& b) { return (a%MOD + b%MOD)%MOD; }
template <typename T>
T subMod(const T& a, const T& b) { return ((a%MOD - b%MOD)%MOD + MOD)%MOD; }
template <typename T>
T mulMod(const T& a, const T& b) { return ((a%MOD) * (b%MOD))%MOD; }

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
void lowestFraction(T& numerator, T& denominator) {
  T GCD = findGCD(numerator, denominator);
  numerator /= GCD;
  denominator /= GCD;
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
  const vector<LL>& FACTORIAL_MOD, T& numerator, T& denominator)
{
  if (N < K) {
    numerator = 0;
    denominator = 1;
    return;
  } else if (N == K) {
    numerator = 1;
    denominator = 1;
    return;
  }  
  numerator = FACTORIAL_MOD[N-1];
  denominator = mulMod(FACTORIAL_MOD[N-K-1], FACTORIAL_MOD[K-1]);
  lowestFraction(numerator, denominator);
}

// Find Prob of getting a chocolate cookies
LL getProb(const LL& C1, const LL& C2, const LL& C3, const LL& C4,
  const vector<LL>& FACTORIAL_MOD, const LL& K)
{
  // Total no. cookies
  LL C = C1 + C2 + C3 + C4;
  // Edge case: K+1 > C1 + C2 + C3
  if (K + 1 > C - C4) {
    return 0;
  }
  // Final prob of getting chocolate cookies: x/y
  // No. ways to pick K+1 cookies not heavier than W1: x1/y1
  // No. ways to pick K+1 cookies that are lighter than W1: x2/y2
  // No. ways to pick K+1 cookies: x3/y3
  LL x, y, x1, y1, x2, y2, x3, y3;
  getCombinatorial(C - C4, K+1, FACTORIAL_MOD, x1, y1);
  getCombinatorial(C2, K+1, FACTORIAL_MOD, x2, y2);
  getCombinatorial(C, K+1, FACTORIAL_MOD, x3, y3);

  // No. ways to pick at least 1 cookies of W1
  x = subMod(mulMod(x1, y2), mulMod(x2, y1));
  y = mulMod(y1, y2);
  lowestFraction(x, y);
  // Prob of picking at least 1 cookies of W1
  x = mulMod(x, y3);
  y = mulMod(y, x3);
  lowestFraction(x, y);
  // Considering tie breaking prob, due to same weights
  if (C3 != 0) {
    x = mulMod(x, C1);
    y = mulMod(y, C1+C3);
    lowestFraction(x, y);
  }
  return mulMod(x, modInverse(y));
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // No. test case T: 1 ≤ T ≤ 1000
  int T; cin >> T;

  // Pre-create an array of the mod of factorial from 1 to 9e6
  vector<LL> FACTORIAL_MOD(9000000, 1);
  for (LL i = 1; i < 9000000; i++) {
    FACTORIAL_MOD[i] = mulMod(FACTORIAL_MOD[i-1], i+1);
  }

  for (size_t t = 1; t <= T; t++) {
    // No. of batches N: 2 ≤ N ≤ 3000
    // No. of times weighting K: 1 ≤ K ≤ 9e6
    int N; LL K; cin >> N >> K;

    // No. of cookies each batch Ci: 1 ≤ Ci ≤ 3000
    // Weight of cookie each batch Wi: 1 ≤ Ci ≤ 1e9
    LL Ci; int Wi;
    // No. of cookies from batch 1: C1, lighter than batch 1: C2
    // equal to batch 1: C3, heavier than batch 1: C4
    LL C1, C2 = 0, C3 = 0, C4 = 0; int W1;
    cin >> C1 >> W1;
    for (size_t n = 1; n < N; n++) {
      cin >> Ci >> Wi;
      if (Wi < W1)
        C2 += Ci;
      else if (Wi == W1)
        C3 += Ci;
      else
        C4 += Ci;
    }
    cout << "Case #" << t << ": "
         << getProb(C1, C2, C3, C4, FACTORIAL_MOD, K) << endl;
  }
  return 0;
}
