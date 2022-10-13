#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <chrono>

using std::cout, std::cin, std::endl, std::ostream;
using std::vector, std::reverse, std::string;
using std::chrono::steady_clock, std::chrono::duration_cast;
using LL = long long;
using secs = std::chrono::seconds;
using mins = std::chrono::minutes;

const int DEBUG_LEVEL = 0;

// Supporting function for: printing and logging
template <typename T>
ostream & operator << (ostream& os, const vector<T>& vec)
{
  cout << "Vector: ";
  for(auto elem : vec)
    os << elem << " ";
  return os;
}
template <class... Args>
void LOGIF(const int& level, Args... args)
{
  if (level > DEBUG_LEVEL) return;
  (cout << ... << args) << "\n";
}

// Return the LSB (least significant bit)
template<typename T>
inline T LSB(const T& i) { return i & ~(i-1); }
// Query Fenwick tree
// https://youtu.be/RgITNht_f4Q
template<typename T>
T queryFenwickTree(const vector<T>& vectIn, int ind)
{
  T output = 0;
  while (ind > 0) {
    output += vectIn[ind];
    ind -= LSB(ind);
  }
  return output;
}
// Build Fenwick tree
template<typename T>
void buildFenwickTree(vector<T>& vectIn, const int& val)
{
  vectIn.insert(vectIn.begin(), val);
  for (size_t i = 1; i < vectIn.size(); i++) {
    if (i + LSB(i) < vectIn.size())
      vectIn[i + LSB(i)] = vectIn[i + LSB(i)] + vectIn[i];
  }
}
// Update Fenwick tree
// NOTE: the input index is from 1 to N, not from 0
// Adding val to the current value, not replacing it
// The array length for the tree is N+1
template<typename T>
void updateFenwickTree(vector<T>& vectIn, const int& val, int ind)
{
  while (ind < vectIn.size()) {
    vectIn[ind] = vectIn[ind] + val;
    ind += LSB(ind);
  }  
}

long long getNumSwap(
  vector<int>* C1, vector<int>* C2,
  vector<LL>* I1, vector<LL>* I2, const int& Zi)
{
  int N = (*C1).size() - 1;   // Total No. tasks
  int N2 = (*C1)[0];          // No. task 2
  int N1 = N - N2;            // No. task 1
  LOGIF(2, "N=", N, " N1=", N1, " N2=", N2);
  
  if (N1%2)                   // Edge case: odd no. task 1
    return -1;

  int sum = (N1 + 2*N2) / 2;  // hafl the sum of all task time
  float avg = (float)sum / Zi;// average time for Zi tasks
  LOGIF(2, "sum=", sum, " avg=", avg);
  if (avg < 1 || avg > 2)     // Out of range average
    return -1;  
  if (avg == 1 && N1 < Zi)    // Edge case: minimum average
    return -1;
  if (avg == 2 && N2 < Zi)    // Edge case: maximum average
    return -1;

  int L, H;   // No. task 2 in Lower and Higher sides
  int d;      // 1/2 of sum difference, also the no. tasks to move
  L = queryFenwickTree(*C1, Zi); // currently left side
  int sumLeft = (Zi-L) + 2*(L);
  LOGIF(2, "sumLeft=", sumLeft, " vs sum=", sum);
  if (sumLeft == sum)
    return 0;
  
  // Variables for the suitable directions
  vector<int> *C; vector<LL> *I; int Z;
  if (sumLeft < sum) {
    d = sum - sumLeft;
    Z = Zi; C = C1; I = I1;
  } else if (sumLeft > sum) {
    d = sumLeft - sum;
    Z = N - Zi; L = N2 - L; C = C2; I = I2;
  }

  if (N2 - L < d)     // Edge case: not enough 2 from higher side
    return -1;
  if (Z-L < d)        // Edge case: not enough 1 from lower side 
    return -1;  

  int s = 1;  // The id from which the subarray will filled with 2s
  while ((L-queryFenwickTree(*C, s)+d != Z-s+1) && (s < Z))
    s++;  
  int t = s;  // The id of the last 2 will be moved
  
  long long sumIndHigh;                 // Indices sum before switches
  LL sumIndLow = (Z-s+1) * (s+Z) / 2;   // Indices sum after switches
  int S1 = queryFenwickTree(*C, s-1);
  while ((t<=N) && (queryFenwickTree(*C, t) - S1 != (Z-s+1)))
    t++;
  sumIndHigh = queryFenwickTree(*I, t);
  if (s > 1)
    sumIndHigh -= queryFenwickTree(*I, s);

  LOGIF(2, "s=", s, " t=", t);
  LOGIF(2, "sumIndLow=", sumIndLow, " sumIndHigh=", sumIndHigh);
  
  return sumIndHigh - sumIndLow;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T; cin >> T;    // No. test case T: 1 ≤ T ≤ 95
  for (size_t t = 1; t <= T; t++) {
    steady_clock::time_point t1 = steady_clock::now();
    int N, M;         // No. tasks N, No. updates M: 1 ≤ N, M ≤ 1e6
    long long Q = 0;  // No. swaps Q
    cin >> N >> M;
    int Xi, Zi;       // Index Xi, Zi: 1 ≤ Xi ≤ N, 1 ≤ Zi ≤ N-1
    int Ai, Yi;       // Task time Ai, Yi: Ai, Yi ∈ {1,2}
    
    vector<int> A(N, 0);  // Binary vector keep track of only task 2
    // 2 (N+1)x1 vector for 2 Fenwick trees of index summation
    vector<LL> I1(N, 0), I2(N, 0);
    int C = 0;        // Total no. task 2
    for (size_t n = 0; n < N; n++) {
      cin >> Ai;
      if (Ai == 2) {
        C ++;
        A[n] = 1;
        I1[n] = n+1;    // The index is +1 for ease
        I2[N-1-n] = N-n;
      }
    }
    // 2 (N+1)x1 vector for 2 Fenwick trees of no. counts
    vector<int> C1(A), C2(A);
    reverse(C2.begin(), C2.end());
    buildFenwickTree(C1, C); buildFenwickTree(C2, C);
    buildFenwickTree(I1, 0); buildFenwickTree(I2, 0);

    LOGIF(1, "Case #", t, ": N=", N, " M=", M);
    LOGIF(2, A, "\n", C1, "\n", C2, "\n", I1, "\n", I2);

    for (size_t m = 1; m <= M; m++) {
      cin >> Xi >> Yi >> Zi;
      LOGIF(1, "Case #", t, ": N=", N, " m=", m, "/", M, " Xi=", Xi, 
          " Yi=", Yi, " Zi=", Zi);
      if (Yi == 1 && A[Xi-1]) {
        A[Xi-1] = 0; *C1.begin() -= 1; *C2.begin() -= 1;
        updateFenwickTree(C1, -1, Xi);
        updateFenwickTree(C2, -1, N+1-Xi);
        updateFenwickTree(I1, -Xi, Xi);
        updateFenwickTree(I2, -(N+1-Xi), N+1-Xi);
      } else if (Yi == 2 && !A[Xi-1]) {
        A[Xi-1] = 1; *C1.begin() += 1; *C2.begin() += 1;
        updateFenwickTree(C1, 1, Xi);
        updateFenwickTree(C2, 1, N+1-Xi);
        updateFenwickTree(I1, Xi, Xi);
        updateFenwickTree(I2, N+1-Xi, N+1-Xi);
      }
      LOGIF(2, A, "\n", C1, "\n", C2, "\n", I1, "\n", I2);
      
      long long Qi = getNumSwap(&C1, &C2, &I1, &I2, Zi);
      Q += Qi;
      LOGIF(2, "Qi=", Qi, " Q=", Q);
    }
    cout << "Case #" << t << ": " << Q << endl;
    steady_clock::time_point t2 = steady_clock::now();
    LOGIF(1, "t = ", duration_cast<secs>(t1 - t2).count(), "[s] = ",
        (float)duration_cast<mins>(t1 - t2).count(), "[min]");
  }
  return 0;
}
