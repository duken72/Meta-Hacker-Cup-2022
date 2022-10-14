#include <iostream>
#include <vector>
#include <math.h>

using std::cout, std::cin, std::endl, std::vector;
using LL = long long;
using vectInt = vector<int>;

const unsigned int MOD = 1000000007;
const unsigned int C = 3000;

// Modular arithmetic
LL modAdd(const LL& a, const LL& b) { return ((a%MOD) + (b%MOD))%MOD; }
LL modMul(const LL& a, const LL& b) { return ((a%MOD) * (b%MOD))%MOD; }

void getCoordinateCounts(const int& numPoints, vectInt& countX, vectInt& countY)
{
  int x, y;                     // Coordinates: 0 ≤ x, y ≤ 3,000
  countX = vectInt(C+1, 0);
  countY = vectInt(C+1, 0);
  for (size_t i = 0; i < numPoints; i++) {
    cin >> x >> y;
    countX[x] = countX[x] + 1;
    countY[y] = countY[y] + 1;
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

// Precompte the square distance array
vector<LL> createSquareDistVect(const int& dim)
{
  vector<LL> output(C+1, 0);
  for (size_t i = 0; i < C+1; i++)
    output[i] = std::pow(i, 2);
  return output;
}

void addDistances(const vector<LL>& distVect, LL& output,
  const vectInt& X, const vectInt& XCount,
  const vectInt& Y, const vectInt& YCount)
{
  LL temp;
  for (auto x : X) {
    for (auto y : Y) {
      temp = (x>=y) ? modMul(distVect[x-y]*XCount[x], YCount[y])
                    : modMul(distVect[y-x]*XCount[x], YCount[y]);
      output = modAdd(output, temp);
    }
  }  
}

LL solve(const vector<LL>& distVect)
{
  LL output = 0;                    // The output square distances
  vectInt AC, BC, XC, YC;           // Vector of coordinate counts
  int N; cin >> N;                  // No. trees N: 2 ≤ N ≤ 500,000
  getCoordinateCounts(N, AC, BC);
  int Q; cin >> Q;                  // No. wells K: 0 ≤ K ≤ 500,000
  getCoordinateCounts(Q, XC, YC);
  vectInt A = getUniqueValues(AC);  // Vector of unique coordinates
  vectInt B = getUniqueValues(BC);  // Vector of unique coordinates
  vectInt X = getUniqueValues(XC);  // Vector of unique coordinates
  vectInt Y = getUniqueValues(YC);  // Vector of unique coordinates
  addDistances(distVect, output, A, AC, X, XC);
  addDistances(distVect, output, B, BC, Y, YC);
  return output;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<LL> distVect = createSquareDistVect(C+1);
  int T; cin >> T;    // No. test cases T: 1 ≤ T ≤ 55
  for (size_t t = 1; t <= T; t++) {
    cout << "Case #" << t << ": " << solve(distVect) << endl;
  }
  cout << "Using precomputed square distance vector" << endl;
  return 0;
}
