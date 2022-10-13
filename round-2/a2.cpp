#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

using std::cout, std::cin, std::endl;
using std::string, std::vector;
using LL = long long;
const int MOD = 27644437;

// Print a vector
template<typename T>
void printVect(const std::vector<T>& vectIn)
{
  for (auto i : vectIn)
    std::cout << i << " ";
  std::cout << "\n";
}

// Addition and subtraction with modulo
template <typename T>
T add(const T& a, const T& b) { return (a % MOD + b % MOD) % MOD; }
template <typename T>
T sub(const T& a, const T& b) { return ((a - b) % MOD + MOD) % MOD; }

// Get hash value (https://stackoverflow.com/q/664014/11397588)
const int hash(int x)
{
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  return ((x >> 16) ^ x) % MOD;
}

// Check if a array is almost perfectly balance
bool checkBalanced(const vector<int>& vectIn)
{
  return true;
}

template <typename T>
class Segment_Tree {
  T value;
  std::pair<int, int> range;
  vector<T> values;
  Segment_Tree* childNode1, childNode2;

  void build(vector<T> vectIn)
  {

  }

public:
  Segment_Tree(vector<T> vectIn)
  {
    
  };

  T query(int index1, int index2) const;
  T at(int index) const;
  void update(int index, int value);
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // No. test case T: 1 ≤ T ≤ 85
  int T; cin >> T;

  for (size_t t = 1; t <= T; t++) {
    // No. of interger N: 1 ≤ N ≤ 10^6
    int N; cin >> N;

    // Read the integer array A: 1 ≤ Ai ≤ 10^6
    vector<int> A(N);
    for (size_t i = 0; i < N; i++) {
      int Ai; cin >> Ai;
      A[i] = Ai;
    }
    printVect(A);

    // No. queries Q: 1 ≤ Q ≤ 10^6
    // No. almost balance arrays C: 1 ≤ C ​≤ Q
    int Q, C = 0; cin >> Q;
    for (size_t q = 1; q <= Q; q++) {
      // Input command: 1 or 2
      // Event 1: Set value at Xi to Yi: 1 ≤ Xi ​≤ N, 1 ≤ Yi ≤ 10^6
      // Event 2: Check subarray from L to R: 1 ≤ Li ≤ Ri ​≤ N
      int C0, C1, C2;
      cin >> C0 >> C1 >> C2;
      if (C0==1) {
        A[C1-1] = C2;
        cout << "new vect: ";
        printVect(A);
      } else if (C0==2) {
        if ((C2 - C1)%2 == 1)
          continue;
        if (C2 == C1) {
          C++;
          continue;
        }        
        vector<int> subA(A.begin()+C1-1, A.begin()+C2);
        printVect(subA);
        C++;
      }
    }
    cout << "Case #" << t << ": " << C << endl;
  }

  cout << MOD << endl;
  cout << 0x45d9f3b << endl;  

  return 0;
}
