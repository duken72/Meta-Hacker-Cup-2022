#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>

using namespace std;
using LL = long long;
const unsigned int MOD = 1'000'000'007;

void getCoordinateAndSum(const int& numPoints, LL& sumX, LL& sumY, LL& sumSquare)
{
  LL x, y;                            // Coordinates: 0 ≤ x, y ≤ 1e9
  sumX = 0; sumY = 0; sumSquare = 0;  // Reset values
  for (size_t i = 0; i < numPoints; i++) {
    cin >> x >> y;
    sumX = (sumX + x) % MOD;
    sumY = (sumY + y) % MOD;
    sumSquare = (sumSquare + (x * x) % MOD + (y * y) % MOD) % MOD;
  }
}

LL solve()
{
  LL sumA, sumB, sumX, sumY;        // Sum of coordinates
  LL sumSquare1, sumSquare2;        // Sum of coordinate squares
  int N; cin >> N;                  // No. trees N: 2 ≤ N ≤ 500,000
  getCoordinateAndSum(N, sumA, sumB, sumSquare1);
  int Q; cin >> Q;                  // No. wells K: 0 ≤ K ≤ 500,000
  getCoordinateAndSum(Q, sumX, sumY, sumSquare2);
  LL output = 0;                    // The output square distances
  output = ((sumSquare1 * Q) % MOD + (sumSquare2 * N) % MOD) % MOD;
  output = (output - (2 * sumA * sumX) % MOD + MOD) % MOD;
  output = (output - (2 * sumB * sumY) % MOD + MOD) % MOD;
  return output;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;    // No. test cases T: 1 ≤ T ≤ 50
  for (size_t t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve() << endl;
  return 0;
}
// Time = 400[ms]