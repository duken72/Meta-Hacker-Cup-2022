#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>

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
  std::ifstream myfileI ("second_hands_input.txt");
  std::ofstream myfileO ("output.txt", std::ios::trunc);
  int T, N, K;
  // T: number of cases
  // N: number of parts
  // K: the capacity of each display cases

  if (myfileI.is_open() && myfileO.is_open()) {
    std::string line;
    std::getline (myfileI,line);
    T = stoi(line);
    
    // Loop over each case
    for (size_t i = 0; i < T; i++)
    {      
      std::getline (myfileI,line);
      std::vector<int> vectIn = stringToVector(line);
      N = vectIn[0];
      K = vectIn[1];
    
      std::getline (myfileI,line);
      std::vector<int> vectPart = stringToVector(line);
      std::vector<int> vectCount;
      for (size_t j = 1; j < 101; j++) {
        vectCount.push_back(std::count(vectPart.begin(), vectPart.end(), j));
      }
      int maxCount = *std::max_element(vectCount.begin(), vectCount.end());
      
      if (N > 2*K or maxCount > 2) {
        myfileO << "Case #" << i+1 << ": NO\n";
      } else {
        myfileO << "Case #" << i+1 << ": YES\n";
      }
    }  
    myfileI.close();
    myfileO.close();
  }
  else std::cout << "Unable to open file for reading";
  
  return 0;
}
