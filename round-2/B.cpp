#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using std::cout, std::cin, std::endl;
using std::string, std::vector;
const int MOD = 1000000007;

struct Client {
  int dayBuy, daySell;
  int valBuy, valSell;
};
struct SaleDay {
  int day;
  
};


struct Path
{
  int sellClient, buyClient, value;
};


// Addition and subtraction with modulo
template <typename T>
T add(const T& a, const T& b) { return (a % MOD + b % MOD) % MOD; }

// Print a vector
template<typename T>
void printVect(const std::vector<T>& vectIn)
{
  for (auto i : vectIn)
    std::cout << i << " ";
  std::cout << "\n";
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // No. test case T: 1 ≤ T ≤ 35
  int T; cin >> T;

  for (size_t t = 1; t <= T; t++) {
    // No. of clients N: 1 ≤ N ≤ 10^6
    // No. of profitable paths K: 1 ≤ K ≤ 10^6
    int N, K; cin >> N >> K;


    // 
    // The profit of possible paths
    vector<int> pathProfits;

    // The sum of K most profitable paths
    int sumProfit = 0;
    for (size_t i = 0; i < K; i++) {
      if (i == pathProfits.size()) break;
      sumProfit += pathProfits[i];
    }    
    cout << "Case #" << t << ": " << sumProfit << endl;
  }
  return 0;
}
