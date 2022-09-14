#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

// Function to read line into vector of int
std::vector<int> stringToVector(std::string str)
{
  std::stringstream iss(str);
  int number;
  std::vector<int> outVect;
  while ( iss >> number )
    outVect.push_back(number);
  return outVect;
}

int main()
{
  std::ifstream myfileI ("consecutive_cuts_chapter_1_input.txt");
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
      // N: number of cards
      // K: number of cuts
      int N, K;
      std::getline (myfileI,line);
      std::vector<int> vectIn = stringToVector(line);
      N = vectIn[0];
      K = vectIn[1];
      std::getline (myfileI,line);
      std::vector<int> vectA = stringToVector(line);
      std::getline (myfileI,line);
      std::vector<int> vectB = stringToVector(line);
      if (K == 0) {
        if (vectA == vectB) {
          myfileO << "YES\n";
        } else myfileO << "NO\n";
        continue;
      }

      // If K = 1, we have to change the order of the cards
      if (K == 1 && vectA == vectB) {
        myfileO << "NO\n";
        continue;
      }
      
      if (N==2) {
        // If K is odd, and we have only 2 cards, we also
        // have to change the order of the cards
        if (K%2 == 1 && vectA == vectB) {
          myfileO << "NO\n";
          continue;
        }
        // If K is even, and we have only 2 cards, we also
        // have to preserve the order of the cards
        if (K%2 == 0 && vectA != vectB) {
          myfileO << "NO\n";
          continue;
        }
      }

      // Out of the above edge cases, if it's possible to cut
      // and reorder, then it would be possible with one single cut
      auto it = std::find(vectA.begin(), vectA.end(), vectB[0]);
      std::vector<int> vectC(it, vectA.end());
      vectC.insert(vectC.end(), vectA.begin(), it);

      if (vectB == vectC) {
        myfileO << "YES\n";
      } else myfileO << "NO\n";
    }
    myfileI.close();
    myfileO.close();
  } else std::cout << "Unable to open file for reading";
  return 0;
}
