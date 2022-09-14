#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


int main()
{
  std::ifstream myfileI ("second_flight_sample_input.txt");
  std::ofstream myfileO ("output.txt", std::ios::trunc);
  // T: number of test cases
  int T;

  if (myfileI.is_open() && myfileO.is_open()) {
    std::string line;
    std::getline (myfileI,line);
    T = stoi(line);
    
    // Loop over each test case
    for (size_t t = 0; t < T; t++) {
      myfileO << "Case #" << t+1 << ":";
    }
    myfileI.close();
    myfileO.close();
  } else std::cout << "Unable to open file for reading";
  return 0;
}
