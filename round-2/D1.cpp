#include <iostream>
#include <vector>

using std::cout, std::cin, std::endl;
using std::vector;

// Return the LSB (least significant bit)
template<typename T>
inline T LSB(const T& i) { return i & ~(i-1); }
// Query Fenwick tree
// https://youtu.be/RgITNht_f4Q
int queryFenwickTree(const vector<int>& vectIn, int ind)
{
  int output = 0;
  while (ind > 0) {
    output += vectIn[ind];
    ind -= LSB(ind);
  }
  return output;
}
// Build Fenwick tree
void buildFenwickTree(vector<int>& vectIn)
{
  for (size_t i = 1; i < vectIn.size(); i++) {
    if (i + LSB(i) < vectIn.size())
      vectIn[i + LSB(i)] = vectIn[i + LSB(i)] + vectIn[i];
  }
}
// Update Fenwick tree
// NOTE: the input index is from 1 to N, not from 0
// Adding val to the current value, not replacing it
// The array length for the tree is N+1
void updateFenwickTree(vector<int>& vectIn, const int& val, int ind)
{
  while (ind < vectIn.size()) {
    vectIn[ind] = vectIn[ind] + val;
    ind += LSB(ind);
  }  
}

long long getNumSwap(
  const vector<int>& vect1, const vector<int>& vect2,
  const vector<int>& vect3, const int& numIn)
{
  long long output = 0;
  // Total no. each type of task
  int C1 = vect1[0];
  int C2 = vect2[0];
  int C3 = vect3[0];
  // Edge case: the total sum is odd
  if ((C1+C3)%2)
    return -1;
  
  // Check sum and average
  int sum = (C1 + 2*C2 + 3*C3) / 2;
  float avg = (float)sum / numIn;
  // Out of range average
  if (avg < 1 || avg > 3)
    return -1;
  // Keep the counts of two side of the array
  int H1, H2, H3, L1, L2, L3;
  L1 = queryFenwickTree(vect1, numIn);
  L3 = queryFenwickTree(vect3, numIn);
  // Edge case: minimum / maximum average
  if (avg == 1)
    return (numIn > C1) ? -1 : numIn - L1;
  if (avg == 3)
    return (numIn > C3) ? -1 : numIn - L3;
  L2 = queryFenwickTree(vect2, numIn);
  
  // Complicated logic now
  int sumLeft = L1 + 2*L2 + 3*L3;
  if (sumLeft == sum) {
    return 0;
  } else if (sumLeft > sum) {
    H1 = L1; L1 = C1 - H1;
    H2 = L2; L2 = C2 - H2;
    H3 = L3; L3 = C3 - H3;
  } else {
    H1 = C1 - L1;
    H2 = C2 - L2;
    H3 = C3 - L3;
  }
  // Try to drive the difference between higher and lower side d to 0
  int d = (H1 + 2*H2 + 3*H3) - (L1 + 2*L2 + 3*L3);
  // Switch 3 from higher side with 1 from lower side
  while (d >= 4 && H3>0 && L1>0) { 
    H3--; H1++; L1--; L3++; output++; d -= 4;
  }
  // Switch 3 from higher side with 2 from lower side
  while (d >= 4 && H3>0 && L2>0) {
    H3--; H2++; L2--; L3++; output++; d -= 2;
  }
  // Switch 2 from higher side with 1 from lower side
  while (d >= 4 && H2>0 && L1>0) {
    H2--; H1++; L1--; L2++; output++; d -= 2;
  }
  if (d == 0)
    return output;
  if (d == 2 && ((H3>0 && L2>0) || (H2>0 && L1>0)))
    return output + 1;
  if (d == -2 && ((H1>0 && L2>0) || (H2>0 && L3>0)))
    return output + 1;
  return -1;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // No. test case T: 1 ≤ T ≤ 100
  int T; cin >> T;
  for (size_t t = 1; t <= T; t++) {
    // No. tasks N: 2 ≤ N ≤ 1e6
    // No. updates M: 1 ≤ M ≤ 1e6
    int N, M; cin >> N >> M;
    // No. swaps Q: 1 ≤ Q ≤ 1e12
    long long Q = 0;
    // Index Xi, Zi: 1 ≤ Xi ≤ N, 1 ≤ Zi ≤ N-1
    int Xi, Zi;
    // Task time Ai, Yi: Ai, Yi ∈ {1,2,3}
    int Ai, Yi;

    // 3 binary vector of length N for each task
    vector<int> T1(N, 0), T2(N, 0), T3(N, 0);
    // 3 vector of length N+1 for 3 Fenwick tree of each task
    vector<int> A1(1, 0), A2(1, 0), A3(1, 0);
    for (size_t n = 1; n <= N; n++) {
      cin >> Ai;
      if (Ai == 1) {
        *A1.begin() += 1; T1[n-1] = 1;
      } else if (Ai == 2) {
        *A2.begin() += 1; T2[n-1] = 1;
      } else { // (Ai == 3)
        *A3.begin() += 1; T3[n-1] = 1;
      }
    }
    A1.insert(A1.end(), T1.begin(), T1.end());
    A2.insert(A2.end(), T2.begin(), T2.end());
    A3.insert(A3.end(), T3.begin(), T3.end());
    buildFenwickTree(A1);
    buildFenwickTree(A2);
    buildFenwickTree(A3);

    for (size_t m = 1; m <= M; m++) {
      cin >> Xi >> Yi >> Zi;
      cout << "Case #" << t << ": N=" << N << " m=" << m << "/" << M << endl;
      if (Yi == 1 && !T1[Xi-1]) {
        updateFenwickTree(A1, 1, Xi);
        T1[Xi-1] = 1; *A1.begin() += 1;
        if (T2[Xi-1]) {
          updateFenwickTree(A2, -1, Xi);
          T2[Xi-1] = 0; *A2.begin() -= 1;
        } else { //T3[Xi-1]
          updateFenwickTree(A3, -1, Xi);
          T3[Xi-1] = 0; *A3.begin() -= 1;
        }
      } else if (Yi == 2 && !T2[Xi-1]) {
        updateFenwickTree(A2, 1, Xi);
        T2[Xi-1] = 1; *A2.begin() += 1;
        if (T1[Xi-1]) {
          updateFenwickTree(A1, -1, Xi);
          T1[Xi-1] = 0; *A1.begin() -= 1;
        } else { //T3[Xi-1]
          updateFenwickTree(A3, -1, Xi);
          T3[Xi-1] = 0; *A3.begin() -= 1;
        }
      } else if (Yi == 3 && !T3[Xi-1]) {
        updateFenwickTree(A3, 1, Xi);
        T3[Xi-1] = 1; *A3.begin() += 1;
        if (T1[Xi-1]) {
          updateFenwickTree(A1, -1, Xi);
          T1[Xi-1] = 0; *A1.begin() -= 1;
        } else { //T2[Xi-1]
          updateFenwickTree(A2, -1, Xi);
          T2[Xi-1] = 0; *A2.begin() -= 1;
        }
      }
      Q += getNumSwap(A1, A2, A3, Zi);
    }
    cout << "Case #" << t << ": " << Q << endl;
  }
  return 0;
}
