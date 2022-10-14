#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>

using std::cout, std::cin, std::endl, std::vector;
using std::chrono::steady_clock, std::chrono::duration_cast;
using LL = long long;
using std::chrono::milliseconds;

const unsigned int MOD = 1000000007;

void getCoordinateAndSum(const int& numPoints, LL& sumX, LL& sumY, LL& sumSquare)
{
  LL x, y;                            // Coordinates: 0 ≤ x, y ≤ 1e9
  sumX = 0; sumY = 0; sumSquare = 0;  // Reset the sum
  for (size_t i = 0; i < numPoints; i++) {
    cin >> x >> y;
    sumX = (sumX + x)%MOD;
    sumY = (sumY + y)%MOD;
    sumSquare = (sumSquare + (x*x)%MOD)%MOD;
    sumSquare = (sumSquare + (y*y)%MOD)%MOD;
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
  output = ((sumSquare1*Q)%MOD + (sumSquare2*N)%MOD)%MOD;
  output = (output - (2*sumA*sumX)%MOD + MOD)%MOD;
  output = (output - (2*sumB*sumY)%MOD + MOD)%MOD;
  return output;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  steady_clock::time_point t1 = steady_clock::now();
  int T; cin >> T;    // No. test cases T: 1 ≤ T ≤ 50
  for (size_t t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve() << endl;
  steady_clock::time_point t2 = steady_clock::now();
  // cout << "Using coordinates' sum in t = "
  //      << duration_cast<milliseconds>(t2 - t1).count() << "[ms]" << endl;
  return 0;
}
