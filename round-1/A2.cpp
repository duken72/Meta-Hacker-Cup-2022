#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

// Major difference is that now the cards are not unique.

// Function to read line into vector of int
std::vector<int> stringToVector(const std::string& str)
{
  std::stringstream iss(str);
  int number;
  std::vector<int> outVect;
  while ( iss >> number )
    outVect.push_back(number);
  return outVect;
}

// Get the value with minimum count in a vector
void getValueWithMinCount(const std::vector<int>& vectIn, int& value, int& count)
{
  // Vector of unique values
  std::vector<int> values(vectIn);
  std::sort(values.begin(), values.end());
  auto last = std::unique(values.begin(), values.end());
  values.erase(last, values.end());

  count = vectIn.size();
  for (size_t i = 0; i < values.size(); i++) {
    if (count > std::count(vectIn.begin(), vectIn.end(), values[i])) {
      value = values[i];
      count = std::count(vectIn.begin(), vectIn.end(), values[i]);
    }
    if (count == 1) break;
  }
}

// Return the new sequence after a cut
std::vector<int> getCutSequence(const std::vector<int>& vectIn, int pos)
{
  std::vector<int> vectOut(vectIn.begin() + pos, vectIn.end());
  vectOut.insert(vectOut.end(), vectIn.begin(), vectIn.begin() + pos);
  return vectOut;
}

int main()
{
  std::ifstream myfileI ("consecutive_cuts_chapter_2_input.txt");
  std::ofstream myfileO ("output.txt", std::ios::trunc);
  // T: number of test cases
  int T;

  if (myfileI.is_open() && myfileO.is_open()) {
    std::string line;
    std::getline (myfileI,line);
    T = stoi(line);
    
    // Loop over each test case
    for (size_t t = 0; t < T; t++) {
      myfileO << "Case #" << t+1 << ": ";
      std::getline (myfileI,line);
      std::vector<int> vectIn = stringToVector(line);
      // N: number of cards
      // K: number of cuts
      int N = vectIn[0];
      int K = vectIn[1];
      
      // vectA: card sequence A
      std::getline (myfileI,line);
      std::vector<int> vectA = stringToVector(line);
      // vectA: card sequence B
      std::getline (myfileI,line);
      std::vector<int> vectB = stringToVector(line);

      // Edge case 1: there is no cut
      if (K == 0) {
        if (vectA == vectB) {
          myfileO << "YES\n";
        } else myfileO << "NO\n";
        continue;
      }

      // Edge case 2: there are only 2 cards
      if (N==2) {
        std::vector<int> vectC{vectA[1], vectA[0]};
        if (K%2 == 1) {
          if (vectB == vectC)
            myfileO << "YES\n";
          else myfileO << "NO\n";
        } else {
          if (vectB == vectA)
            myfileO << "YES\n";
          else myfileO << "NO\n";
        }
        continue;
      }

      /**
       * @brief Since the cards are no longer distint. Finding random
       * card won't work. We will find the one with the minimum number
       * of counts.
       */

      // v: value with min count
      // c: count of value with min count
      int v, c;
      getValueWithMinCount(vectA, v, c);
      int itA = std::find(vectA.begin(), vectA.end(), v) - vectA.begin();      
      std::vector<int> iterBs;
      std::vector<int>::iterator itB = vectB.begin();
      for (size_t i = 0; i < c; i++) {
        itB = std::find(itB, vectB.end(), v);
        iterBs.push_back(itB - vectB.begin());
        itB++;
      }     
      
      // Create a vector of all possible cut sequence
      std::vector<std::vector<int>> sequences;
      for (size_t i = 0; i < c; i++) {
        if (iterBs[i] == itA) {
          sequences.push_back(vectA);
          continue;
        } else if (itA > iterBs[i]) {
          sequences.push_back(getCutSequence(vectA, itA - iterBs[i]));
        } else {
          sequences.push_back(getCutSequence(vectA, N + itA - iterBs[i]));
        }                        
      }

      if (std::count(sequences.begin(), sequences.end(), vectB) == 0) {
        myfileO << "NO\n";
        continue;
      }

      // Edge case: K=1, N=3
      if (K == 1 && N == 3 && c == 1 && vectA == vectB) {
        myfileO << "NO\n";
        continue;
      }      
      myfileO << "YES\n";
    }
    myfileI.close();
    myfileO.close();
  } else std::cout << "Unable to open file for reading";
  return 0;
}
