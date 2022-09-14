#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <set>
#include <chrono>

// This is insanely fast and efficient
// Even better than B1's approach

const unsigned int M = 1000000007;

// Function to read line into vector of int
std::vector<long long> stringToVector(std::string str)
{
  std::stringstream iss(str);
  int number;
  std::vector<long long> outVect;
  while ( iss >> number )
    outVect.push_back(number);
  return outVect;
}

int main()
{
  std::ifstream myfileI ("watering_well_chapter_2_input.txt");
  std::ofstream myfileO ("output.txt", std::ios::trunc);

  if (myfileI.is_open() && myfileO.is_open()) {
    // T: number of test cases
    int T;

    std::string line;
    std::getline (myfileI,line);
    T = stoi(line);
    
    // Loop over each test case
    for (size_t t = 0; t < T; t++) {
      myfileO << "Case #" << t+1 << ": ";
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

      // Vectors of trees and wells' coordinate
      std::vector<long long> X, Y, A, B;
      std::vector<long long> temp;

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
      long long sumA=0, sumB=0;
      for (auto a : A)
        sumA = (sumA + a)%M;
      for (auto b : B)
        sumB = (sumB + b)%M;
      
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
      long long sumX=0, sumY=0;
      for (auto x : X)
        sumX = (sumX + x)%M;
      for (auto y : Y)
        sumY = (sumY + y)%M;
      
      // Take sum square dist
      std::cout << "Case #" << t+1 << ": " << N << " trees, " << Q << " wells\n";
      // Some modulo formulas
      // ( a + b) % c = ( ( a % c ) + ( b % c ) ) % c
      // ( a – b) % c = ( ( a % c ) – ( b % c ) ) % c
      // ( a * b) % c = ( ( a % c ) * ( b % c ) ) % c

      long long dist = 0;
      for (size_t a = 0; a < A.size(); a++) {
        dist += (Q * (((A[a]%M) * (A[a]%M))%M))%M;
        dist = dist%M;
      }
      for (size_t b = 0; b < B.size(); b++) {
        dist += (Q * (((B[b]%M) * (B[b]%M))%M))%M;
        dist = dist%M;
      }
      for (size_t x = 0; x < X.size(); x++) {
        dist += (N * (((X[x]%M) * (X[x]%M))%M))%M;
        dist = dist%M;
      }
      for (size_t y = 0; y < Y.size(); y++) {
        dist += (N * (((Y[y]%M) * (Y[y]%M))%M))%M;
        dist = dist%M;
      }
      dist -= (2 * ((sumA * sumX)%M))%M;
      dist = (dist+M)%M;
      dist -= (2 * ((sumB * sumY)%M))%M;
      dist = (dist+M)%M;

      myfileO << dist << "\n";
      std::cout << dist << "\n";
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      std::cout << "Time difference = "
                << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
                << "[ms]" << std::endl;
    }
    myfileI.close();
    myfileO.close();
  } else std::cout << "Unable to open file for reading";
  return 0;
}
