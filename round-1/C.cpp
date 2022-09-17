#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <limits.h>

// 20m43s

const long long MAX = -1;

// Print a vector
template<typename T>
void printVect(const std::vector<T>& vectIn)
{
  for (auto i : vectIn) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}

// Get square travel distance between two houses
long long getTravelDist(const std::vector<long long>& houseIn1,
                        const std::vector<long long>& houseIn2)
{
  return std::pow(houseIn1[0]-houseIn2[0], 2) + 
      std::pow(houseIn1[1]-houseIn2[1], 2);
}

// Comparator function based on square distance from a point
struct sortD {
  std::vector<long long> ref_;
  sortD(const std::vector<long long>& ref) { ref_ = ref; }
  bool operator() (const std::vector<long long>& v1,
                  const std::vector<long long>& v2)
  {
    return getTravelDist(v1, ref_) < getTravelDist(v2, ref_);
  }
};

// Function to read line into vector of long long
// Since 0 ≤ Xi, Yi​ ≤ 1,000,000
std::vector<long long> stringToVector(const std::string& str)
{
  std::stringstream iss(str);
  long long number;
  std::vector<long long> outVect;
  while ( iss >> number )
    outVect.push_back(number);
  return outVect;
}

// Get brand damage travel between two houses
long long getBrandDamage(const long long& K,
    const std::vector<long long>& houseIn1,
    const std::vector<long long>& houseIn2)
{
  long long dist = 0;
  dist += std::pow(houseIn1[0]-houseIn2[0], 2);
  dist += std::pow(houseIn1[1]-houseIn2[1], 2);
  return std::max(K, dist);
}

// Get minimum brand damage, when travelling between
// houses via Dijkstra's path planning algorithm
long long getBrandDamagePath(const long long& K, const long long& D,
    const std::vector<std::vector<long long>>& houses)
{
  // Init distances from start house
  std::vector<long long> dist(houses.size(), MAX);
  dist[0] = 0;
  for (size_t j = 1; j < houses.size(); j++) {
    if (getTravelDist(houses[0], houses[j]) > std::pow(D, 2))
      continue;
    dist[j] = getBrandDamage(K, houses[0], houses[j]);
  }
  // std::cout << std::endl; printVect(dist);

  size_t iter = 0;
  for (size_t indSrc = 1; indSrc < houses.size()-1; indSrc++) {
    std::cout << "Total points: " << houses.size()-2
              << " Iter:" << iter << "\n";
    bool greaterX = false;
    iter++;

    if (dist[indSrc] == MAX) continue;
    std::vector<long long> src = houses[indSrc];
    for (size_t indEnd = indSrc+1; indEnd < houses.size(); indEnd++) {
      std::vector<long long> dest = houses[indEnd];
      if (dest[0] - src[0] > D) {
        greaterX = true;
        break;
      }
      if (getTravelDist(src, dest) > std::pow(D,2)) continue;
      if (dist[indEnd] == MAX) {
        dist[indEnd] = dist[indSrc] + getBrandDamage(K, src, dest);
        continue;
      }
      if (dist[indSrc] + getBrandDamage(K, src, dest) < dist[indEnd]) {
        dist[indEnd] = dist[indSrc] + getBrandDamage(K, src, dest);
      }
    }
    // Check if for this current source node, destination nodes
    // are already too far. Then skip checking even further nodes
    if (greaterX) continue;
  }
  // Return distance to the target house (which is at the end)
  return dist[houses.size()-1];
}

int main()
{
  // std::ifstream myfileI ("1.txt");
  std::ifstream myfileI ("lemonade_life_input.txt");
  // std::ifstream myfileI ("lemonade_life_sample_input.txt");
  std::ofstream myfileO ("output.txt", std::ios::trunc);

  if (myfileI.is_open() && myfileO.is_open()) { 
    std::string line;
    std::getline(myfileI,line);
    // T: number of test cases        (1 ≤ T ≤ 90)
    int T = stoi(line);
    
    // Loop over each test case
    for (size_t t = 0; t < T; t++) {
      myfileO << "Case #" << t+1 << ": ";
      std::getline(myfileI,line);
      std::vector<long long> vectIn = stringToVector(line);
      // N: no. of houses               (2 ≤ N ≤ 1,000,000)
      int N = vectIn[0];
      // K: threshold for brand damage  (0 ≤ K ≤ 10^9)
      long long K = vectIn[1];
      // D: maximum distance            (0 ≤ D ≤ 10^9)
      long long D = vectIn[2];
      std::cout << "Case #" << t+1 << ": " << N << " houses, K = "
                << K << ", D = " << D << std::endl;      
      
      long long brandDamage = MAX;
      std::vector<std::vector<long long>> houses;
      std::ofstream qhullFileIn ("qhullIn.txt", std::ios::trunc);

      if (qhullFileIn.is_open()) {
        qhullFileIn<<"2 rbox " << N << " D2\n";
        qhullFileIn<< N <<"\n";
        for (size_t n = 0; n < N; n++) {
          std::getline(myfileI,line);
          houses.push_back(stringToVector(line));
          qhullFileIn << line << "\n";
        }
        qhullFileIn.close();
      } else std::cout << "Unable to open qhullIn.txt for writing";

      // Egde case 1: there are only 2 houses
      if (N == 2) {
        if (getTravelDist(houses[0], houses[1]) <= std::pow(D,2)) {
          brandDamage = getBrandDamage(K, houses[0], houses[1]);
        }
        myfileO << brandDamage << "\n";
        std::cout << "brandDamage = " << brandDamage << "\n\n";
        system("rm qhullIn.txt");
        continue;
      }

      // Find convex hull with Qhull library
      // Qhull's C++ API is complicated, so I go with CLI
      std::cout << "Finding points on convex hull.. ";
      system("qhull < qhullIn.txt Fx > qhullOut.txt");
      std::ifstream qhullFileOut ("qhullOut.txt");
      // Vector of indeces of houses on the convex hull
      std::vector<size_t> indPass;
      if (qhullFileOut.is_open()) {
        if (qhullFileOut.peek() == std::ifstream::traits_type::eof()) {
          if (getTravelDist(houses[0], houses[N-1]) <= std::pow(D,2)) {
            brandDamage = getBrandDamage(K, houses[0], houses[N-1]);
          }
          myfileO << brandDamage << "\n";
          std::cout << "brandDamage = " << brandDamage << "\n\n";
          continue;
        }
        std::getline(qhullFileOut,line);
        int noPoints = stoi(line);
        for (size_t i = 0; i < noPoints; i++) {
          std::getline(qhullFileOut,line);
          indPass.push_back(stoi(line));
        }
        qhullFileOut.close();
      } else std::cout << "Unable to open qhullOut.txt for reading";      
      system("rm qhullIn.txt");
      system("rm qhullOut.txt");
      std::cout << "DONE. There are " << indPass.size() << " points\n";

      // Sorting before applying Dijkstra's algorithm
      std::cout << "Sorting houses from closer to further from start.. ";
      std::vector<std::vector<long long>> passHouses;
      for (size_t i = 0; i < indPass.size(); i++) {
        passHouses.push_back(houses[indPass[i]]);
      }
      // Remove the target house first, add it back in the end
      std::sort(passHouses.begin(), passHouses.end(), sortD(houses[0]));
      // Test 1
      passHouses.erase(std::find(passHouses.begin(), passHouses.end(), houses[N-1]) + 1, passHouses.end());
      // Original: 2 lines
      // passHouses.erase(std::find(passHouses.begin(), passHouses.end(), houses[N-1]));
      // passHouses.push_back(houses[N-1]);
      std::cout << "DONE\n";

      // Applying Dijkstra's algorithm
      std::cout << "Solving Dijkstra's algorithm.. ";
      brandDamage = getBrandDamagePath(K, D, passHouses);
      std::cout << "DONE" << "\n";

      myfileO << brandDamage << "\n";
      std::cout << "brandDamage = " << brandDamage << "\n\n";
    }
    myfileI.close();
    myfileO.close();
  } else std::cout << "Unable to open file for reading & writing";
  return 0;
}
