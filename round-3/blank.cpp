#include <iostream>
#include <vector>
#include <string>

using std::cout, std::cin, std::endl, std::ostream;
using std::vector, std::string;

const int DEBUG_LEVEL = 0;

// Supporting function for: printing and logging
template <typename T>
ostream & operator << (ostream& os, const vector<T>& vec)
{
  cout << "Vector: ";
  for(auto elem : vec)
    os << elem << " ";
  return os;
}
template <class... Args>
void LOGIF(const int& level, Args... args)
{
  if (level > DEBUG_LEVEL) return;
  (cout << ... << args) << "\n";
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T; cin >> T;    // No. test case T: 1 ≤ T ≤ ??
  for (size_t t = 1; t <= T; t++) {
    cout << "Case #" << t << ": " << endl;
  }
  return 0;
}
