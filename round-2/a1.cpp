#include <iostream>
#include <string>
#include <vector>

using std::cout, std::cin, std::endl;
using std::string, std::vector, std::abs;
using vectInt = vector<int>;
using vectCounts = vector<vector<int>>;

// Overload operator - for vectors
vectInt operator -(const vectInt& vect1, const vectInt& vect2)
{
  vectInt vectOut(26);
  for (size_t i = 0; i < 26; i++)
    vectOut[i] = vect1[i] - vect2[i];
  return vectOut;
}

// Count alphabet chars in a string along its length
vectCounts countChars(const string& inString)
{
  int charId, aId = int('a');           // Char to indices
  int N = inString.size();              // String length
  vectInt totalChars(26, 0);
  vectCounts charCounts(N, vectInt(26, 0));   // The Nx26 matrix of counts
  for (size_t i = 0; i < N; i++) {
    charId = int(inString[i]) - aId;
    totalChars[charId] = totalChars[charId] + 1;
    charCounts[i] = totalChars;
  }
  return charCounts;
}

// Get the char counts in specific range
vectInt getCounts(const vectCounts& charCounts, int id)
{
  vectInt output(26,0);
  for (size_t i = 0; i < 26; i++)
    output[i] = charCounts[id][i];
  return output;
}
vectInt getCounts(const vectCounts& charCounts, int id1, int id2)
{
  return (id1 == 0) ? getCounts(charCounts, id2)
                    : getCounts(charCounts, id2) - getCounts(charCounts, id1-1);
}

// Check if the dist between two vectors is 0 or 1
bool compare(const vectInt& vect1, const vectInt& vect2)
{
  int diff = 0;
  for (size_t i = 0; i < 26; i++) {
    diff += abs(vect1[i] - vect2[i]);
    if (diff >=2) return false;
  }
  return true;
}

/**
 * A string is ALMOST perfectly balanced, NOT perfectly balanced, if:
 * Criterion 0: Odd number of chars
 * Criterion 1: There is 1 char with odd number of instances
 * Criterion 2: Two half strings have the same no. char instances
 */
bool checkSubstring(int L, int R, const vectCounts& charCounts)
{
  if (L==R)         // Edge case #1: only 1 char
    return true;
  if ((R-L)%2==1)   // Criterion 0: odd no. chars
    return false;
  bool hasOddChar = false;
  vectInt C0 = getCounts(charCounts, L, R);
  for (int val : C0) {
    if (val%2==1) {
      if (!hasOddChar)
        hasOddChar = true;
      else
        return false;   // Criterion 1: only 1 odd char
    }    
  }
  int M = (L+R)/2;
  vectInt C1, C2, C3, C4;     // No. char in substrings
  C1 = getCounts(charCounts, L, M-1);
  C2 = getCounts(charCounts, M, R);
  C3 = getCounts(charCounts, L, M);
  C4 = getCounts(charCounts, M+1, R);  
  return (compare(C1, C2) || compare(C3, C4)) ? true : false;
}

int solve()
{
  string S; cin >> S; // Input S: 1 ≤ ∣S∣ ≤ 10^6, Si ∈ {'a', ..., 'z'}
  int Q; cin >> Q;    // No. queries Q: 1 ≤ Q ≤ 10^6
  int C = 0;          // No. almost perfect string C: 1 ≤ C ≤ 10^6
  int L = 0, R = 0;   // Positions L, R: 1 ≤ Li ≤ Ri ≤ ∣S∣
  vectCounts charCounts = countChars(S);
  for (size_t q = 0; q < Q; q++) {
    cin >> L >> R; L--; R--;
    if (checkSubstring(L, R, charCounts))
      C += 1;
  }
  return C;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;      // No. test cases T: 1 ≤ T ≤ 90
  for (size_t t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve() << endl;
  return 0;
}
// 17-21 secs
