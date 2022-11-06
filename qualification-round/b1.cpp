#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <string>

using namespace std;
const char EMPTY = '.', TREE = '^';

/**
 * It would be impossible if the width or height is 1,
 * unless there is no tree. Otherwise, it is always possible.
 * Simply add trees to all positions would work
 */
struct Scene {
  int row_;
  int column_;
  vector<vector<char>> scene_;

  Scene(int row, int column) : row_(row), column_(column),
    scene_(row, vector(column, EMPTY)) {}

  bool haveTree() const {
    for (size_t r = 0; r < row_; r++) {
      for (size_t c = 0; c < column_; c++) {
        if (scene_[r][c] == TREE)
          return true;
      }
    }
    return false;
  }
};

string solve()
{
  int R, C; cin >> R >> C;  // No. rows & columns: 1 ≤ R, C ≤ 100
  char space;               // Map space: tree '^' or blank '.'
  Scene scene(R, C);
  for (size_t r = 0; r < R; r++) {
    for (size_t c = 0; c < C; c++)
      cin >> scene.scene_[r][c];
  }
  bool haveTree = scene.haveTree();
  if ((scene.row_==1 || scene.column_==1) && haveTree)
    return "Impossible";
  string result = "Possible";
  for (size_t r = 0; r < R; r++) {
    result += '\n';
    for (size_t c = 0; c < C; c++)
      result += haveTree ? TREE : EMPTY;
  }
  return result;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;          // No. test case T: 1 ≤ T ≤ 85
  for (int t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve() << endl;
  return 0;
}
// Time t = 5[ms]