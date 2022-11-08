#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>

using namespace std;

using LL = long long;
using vectInt = vector<int>;
const unsigned int MOD = 1'000'000'007;
const unsigned int C = 3000;

// Precompte the square distance array
vector<LL> createSquareDistVect(const int& dim)
{
  vector<LL> output(C+1, 0);
  for (size_t i = 0; i < C+1; i++)
    output[i] = i * i;
  return output;
}
static const vector<LL> distVect = createSquareDistVect(C+1);

// Modular arithmetic
LL modMul(const LL& a, const LL& b) { return (a * (b % MOD)) % MOD; }

void getCoordinateCounts(const int& numPoints,
  vectInt& countX, vectInt& countY)
{
  countX = vectInt(C+1, 0);
  countY = vectInt(C+1, 0);
  for (size_t i = 0, x, y; i < numPoints; i++) {
    cin >> x >> y;    // Coordinates: 0 ≤ x, y ≤ 3,000
    countX[x]++;
    countY[y]++;
  }  
}

vectInt getUniqueValues(const vectInt& vectIn)
{
  vectInt output;
  for (size_t i = 0; i <= C; i++) {
    if (vectIn[i] > 0)
      output.push_back(i);
  }
  return output;
}

void addDistances(LL& output,
  const vectInt& X, const vectInt& XCount,
  const vectInt& Y, const vectInt& YCount)
{
  LL temp;
  for (auto x : X) {
    for (auto y : Y) {
      temp = (x >= y) ? modMul(distVect[x-y], XCount[x] * YCount[y])
                      : modMul(distVect[y-x], XCount[x] * YCount[y]);
      output = (output + temp) % MOD;
    }
  }  
}

LL solve()
{
  vectInt AC, BC, XC, YC;           // Vector of coordinate counts
  int N; cin >> N;                  // No. trees N: 2 ≤ N ≤ 500,000
  getCoordinateCounts(N, AC, BC);
  int Q; cin >> Q;                  // No. wells K: 0 ≤ K ≤ 500,000
  getCoordinateCounts(Q, XC, YC);
  vectInt A = getUniqueValues(AC);  // Vector of unique coordinates
  vectInt B = getUniqueValues(BC);  // Vector of unique coordinates
  vectInt X = getUniqueValues(XC);  // Vector of unique coordinates
  vectInt Y = getUniqueValues(YC);  // Vector of unique coordinates
  LL output = 0;                    // The output square distances
  addDistances(output, A, AC, X, XC);
  addDistances(output, B, BC, Y, YC);
  return output;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;    // No. test cases T: 1 ≤ T ≤ 55
  for (size_t t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve() << endl;
  return 0;
}
// Time = 6.3[s]