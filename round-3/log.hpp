#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>

using std::cout, std::cin, std::endl;
using std::ostream;
using std::vector, std::unordered_map;
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
  cout << endl;
  return os;
}
template <typename T1, typename T2>
ostream & operator << (ostream& os, const unordered_map<T1, T2> map)
{
  cout << "Map:\n";
  for( const auto& [key, value] : map )
    os << key << " " << value << endl;
  return os;
}
template <class... Args>
void LOGIF(const int& level, Args... args)
{
  if (level > DEBUG_LEVEL) return;
  (cout << ... << args) << "\n";
}