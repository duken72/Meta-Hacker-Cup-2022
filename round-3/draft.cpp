#include <iostream>
#include <vector>
const int DEBUG_LEVEL = 2;
#include "log.hpp"

using std::cout, std::cin, std::endl;
using std::vector;

int solve() {}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T; cin >> T;    // No. test case T: 1 ≤ T ≤ ??
  for (size_t t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve() << endl;
  return 0;
}
