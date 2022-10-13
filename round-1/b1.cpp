#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <set>

const unsigned int M = 1000000007;
const unsigned int C = 3000;

void printVect(const std::vector<int>& vectIn)
{
  for (auto i : vectIn) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}

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

/**
 * @brief Find uniques values in vectIn and count instances
 * 
 * @param vectIn: the original vector
 * @param vectCount: the vector with instance counts
 */
void getValuesAndCounts(std::vector<int>& vectIn, std::vector<int>& vectCount)
{
  std::set<int> values(vectIn.begin(), vectIn.end());
  vectCount.clear();
  for (int value : values) {
    vectCount.push_back(std::count(vectIn.begin(), vectIn.end(), value));
  }
  vectIn.clear();
  vectIn = std::vector<int>(values.begin(), values.end());
}

int main()
{
  std::ifstream myfileI ("watering_well_chapter_1_input.txt");
  std::ofstream myfileO ("output.txt", std::ios::trunc);

  std::vector<std::vector<long long>> squareDist(C+1, std::vector<long long>(C+1, 0));
  for (size_t i = 0; i < C+1; i++) {
    for (size_t j = 0; j < C+1; j++) {
      if (i == j) continue;
      if (i > j) {
        squareDist[i][j] = squareDist[j][i];
        continue;
      }
      squareDist[i][j] = std::pow(j - i, 2);
    }
  }

  if (myfileI.is_open() && myfileO.is_open()) {
    // T: number of test cases
    int T;

    std::string line;
    std::getline (myfileI,line);
    T = stoi(line);
    
    // Loop over each test case
    for (size_t t = 0; t < T; t++) {
      myfileO << "Case #" << t+1 << ": ";

      // Vectors of trees and wells' coordinate
      std::vector<int> X, Y, A, B;
      // Vectors of value counts in X, Y, A, B
      std::vector<int> XC, YC, AC, BC;
      std::vector<int> temp;

      // Get the trees' coordinates
      std::getline (myfileI,line);
      // N: number of trees
      int N = stoi(line);
      for (size_t n = 0; n < N; n++) {
        std::getline (myfileI,line);
        temp = stringToVector(line);
        A.push_back(temp[0]);
        B.push_back(temp[1]);
      }
      
      // Get the wells' coordinates
      std::getline (myfileI,line);
      // Q: number of wells
      int Q = stoi(line);
      for (size_t q = 0; q < Q; q++) {
        std::getline (myfileI,line);
        temp = stringToVector(line);
        X.push_back(temp[0]);
        Y.push_back(temp[1]);
      }

      std::cout << "Case #" << t+1 << ": " << N << " trees, " << Q << " wells\n";
      std::cout << "Counting instances in A & B...\n";
      getValuesAndCounts(A, AC);
      getValuesAndCounts(B, BC);
      std::cout << "Counting instances in X & Y...\n";
      getValuesAndCounts(X, XC);
      getValuesAndCounts(Y, YC);

      // Take sum square dist
      std::cout << "Taking sum ...\n";
      // Some modulo formulas
      // ( a + b) % c = ( ( a % c ) + ( b % c ) ) % c
      // ( a * b) % c = ( ( a % c ) * ( b % c ) ) % c
      long long dist = 0;
      for (size_t a = 0; a < A.size(); a++) {
        for (size_t x = 0; x < X.size(); x++) {
          dist += (squareDist[A[a]][X[x]] * AC[a] * XC[x]) %M;
          dist = dist%M;
        }
      }
      for (size_t b = 0; b < B.size(); b++) {
        for (size_t y = 0; y < Y.size(); y++) {
          dist += (squareDist[B[b]][Y[y]] * BC[b] * YC[y]) %M;
          dist = dist%M;
        }
      }
      myfileO << dist << "\n";
      std::cout << dist << "\n";
    }
    myfileI.close();
    myfileO.close();
  } else std::cout << "Unable to open file for reading\n";
  return 0;
}
