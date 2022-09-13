#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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
  std::ifstream myfileI ("second_flight_sample_input.txt");
  std::ofstream myfileO ("output.txt", std::ios::trunc);
  // T: number of test cases
  // N: number of airports
  // M: number of flight paths
  // Q: number of days
  int T, N, M, Q;

  if (myfileI.is_open() && myfileO.is_open()) {
    std::string line;
    std::getline (myfileI,line);
    T = stoi(line);
    
    // Loop over each test case
    for (size_t t = 0; t < T; t++) {
      myfileO << "Case #" << t+1 << ":";
      std::getline (myfileI,line);
      std::vector<int> vectIn = stringToVector(line);
      N = vectIn[0];
      M = vectIn[1];
      Q = vectIn[2];
      
      // Read matrix C(N x N), with 1≤ Ci ≤ 10^9
      std::vector<std::vector<int>> C(N, std::vector(N, 0));
      for (size_t m = 0; m < M; m++) {
        std::getline (myfileI,line);
        std::vector<int> vectIn = stringToVector(line);
        C[vectIn[0] - 1][vectIn[1] - 1] = vectIn[2];
        C[vectIn[1] - 1][vectIn[0] - 1] = vectIn[2];
      }

      // Calculate for day q
      for (size_t q = 0; q < Q; q++) {
        std::getline (myfileI,line);
        std::vector<int> vectIn = stringToVector(line);
        int x = vectIn[0] - 1;
        int y = vectIn[1] - 1;
        int f = 0;
        f += 2 * C[x][y];
        for (size_t i = 0; i < N; i++) {
          if (i == y) continue;
          if (C[x][i] != 0) {
            if (C[i][y] != 0) {
              f += std::min(C[x][i], C[i][y]);
            }
          }
        }
        myfileO << " " << f;
      }
      myfileO << "\n";
    }
    myfileI.close();
    myfileO.close();
  } else std::cout << "Unable to open file for reading";
  return 0;
}
