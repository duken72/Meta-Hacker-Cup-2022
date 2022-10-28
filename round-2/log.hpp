#include <iostream>
#include <vector>
#include <chrono>

using std::cout, std::cin, std::endl;
using std::ostream;
using std::vector;
using std::chrono::steady_clock, std::chrono::duration_cast;
using sec = std::chrono::seconds;
using mins = std::chrono::minutes;

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