#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>

using namespace std;

using LL = long long;
using vectInt = vector<int>;
const unsigned int MOD = 1'000'000'007;
const unsigned int C = 3000;

// Precompte the square distance matrix
vector<vector<LL>> createSquareDistMatrix(const int& dim)
{
  vector<vector<LL>> output(C+1, vector<LL>(C+1, 0));
  for (size_t i = 0; i < C+1; i++) {
    for (size_t j = 0; j < C+1; j++) {
      if (i == j)
        continue;
      if (i > j) {
        output[i][j] = output[j][i];
        continue;
      }
      output[i][j] = (j - i) * (j - i);
    }
  }
  return output;
}
static const vector<vector<LL>> distMatrix = createSquareDistMatrix(C+1);

// Modular arithmetic
LL modAdd(const LL& a, const LL& b) { return (a + (b % MOD)) % MOD; }
LL modMul(const LL& a, const LL& b) { return (a * (b % MOD)) % MOD; }

void getCoordinateCounts(const int& numPoints,
  vectInt& countX, vectInt& countY)
{
  countX = vectInt(C+1, 0);
  countY = vectInt(C+1, 0);
  for (int i = 0, x, y; i < numPoints; i++) {
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

void addDistances(LL& output, const vectInt& X, const vectInt& XCount,
  const vectInt& Y, const vectInt& YCount)
{
  for (auto x : X) {
    for (auto y : Y)
      output = modAdd(output,
                      modMul(distMatrix[x][y], XCount[x]*YCount[y]));
  }
}

LL solve()
{
  vectInt AC, BC, XC, YC;           // Vector of coordinate counts
  int N; cin >> N;                  // No. trees N: 2 ≤ N ≤ 500,000
  getCoordinateCounts(N, AC, BC);
  int Q; cin >> Q;                  // No. wells Q: 0 ≤ Q ≤ 500,000
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
// Time = 8.378[s]