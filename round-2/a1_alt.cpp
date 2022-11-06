// Initial draft. Okayish, but NOT for large test cases
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

// Count alphabet char in a string
vector<int> countChar(const string& inString) {
  vector<int> count(26);
  for (size_t i = 0; i < 26; i++)
    count[i] = std::count(inString.begin(), inString.end(), 'a'+i);    
  return count;
}

// Take the subtraction of two count vectors
vector<int> subtractVect(
  const vector<int>& vect1, const vector<int>& vect2) {
  vector<int> vectOut(26);
  for (size_t i = 0; i < 26; i++)
    vectOut[i] = vect1[i] - vect2[i];
  return vectOut;
}

// Check if the dist between two vectors is 0 or 1
bool compareVect(
  const vector<int>& vect1, const vector<int>& vect2) {
  int diff = 0;
  for (size_t i = 0; i < 26; i++) {
    diff += std::abs(vect1[i] - vect2[i]);
    if (diff >=2)
      return false;    
  }
  return true;
}

/**
 * A string is (almost) perfectly balanced if:
 * NOTE: we want almost balanced strings, NOT perfectly balanced
 * 
 * Criterion 0: Odd number of chars
 * Criterion 1: Numbers of each char
 *  There is 0 or 1 char with odd number of occurances
 * Criterion 2: Order of char (after satisfy 1st criterion)
 *  The 1st half of the string needs to have half of all the no. each
 *  type of char
 * NOTE: Take advatange of the fack that we have only alphabet char
 * Si ∈ {'a', ..., 'z'}
 */
bool isAlmostPerfectString(const string& inString)
{
  // Edge case #1: only 1 char
  if (inString.size() == 1)
    return true;
  // Count alphabet characters in the string
  vector<int> c0 = countChar(inString);  
  // Check criterion 1: No. each character
  bool hasOddChar = false;
  for (int i : c0) {
    if (i%2 == 1) {
      if (!hasOddChar)
        hasOddChar = true;
      else
        return false;
    } 
  }
  // Check criterion 2: There is two possible half strings
  string halfString1 = inString.substr(0, (inString.size()-1)/2 + 1);
  string halfString2 = inString.substr(0, (inString.size()-1)/2);

  vector<int> c1, c2, c3, c4;
  c1 = countChar(halfString1);
  c2 = subtractVect(c0, c1);
  c3 = countChar(halfString2);
  c4 = subtractVect(c0, c3);

  return compareVect(c1, c2) || compareVect(c3, c4) ? true : false;
}

int main()
{
  int T; cin >> T;        // No. test case T: 1 ≤ T ≤ 90
  for (size_t t = 1; t <= T; t++) {
    string S;             // Input string S: 1 ≤ ∣S∣ ≤ 10^6
    int Q, C = 0;         // No. queries Q: 1 ≤ C ≤ Q ≤ 10^6
    int L = 0, R = 0;     // Query positions L, R: 1 ≤ Li ≤ Ri ≤ ∣S∣
    cin >> S >> Q;
    for (size_t q = 0; q < Q; q++) {
      cin >> L >> R;
      // Criterion 0: The string has to have odd no. char
      if ((R-L)%2 == 1)
        continue;
      if (isAlmostPerfectString(S.substr(L-1, R-L+1)))
        C += 1;
    }    
    cout << "Case #" << t << ": " << C << endl;
  }
  return 0;
}
