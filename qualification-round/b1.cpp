#include <iostream>
#include <vector>
#include <string>

using std::cout, std::cin, std::endl;
using std::vector, std::string;

/**
 * It would be impossible if either the width or height is 1
 * unless there is no tree. 
 * Otherwise, it is always possible
 * Simply add trees to all positions would work
 * But a less overkill approach would be create 2x2 blocks of trees 
 */

class Scene
{
public:
  int row_;
  int column_;
  vector<vector<bool>> scene_;

  Scene(int row, int column);
  bool haveTree();
  bool checkTree(int row, int column);
  bool addTree(int row, int column);
  void print();
};

Scene::Scene(int row, int column)
{
  row_ = row;
  column_ = column;
  vector<vector<bool>> scene(row, vector<bool>(column, false));
  scene_ = scene;
}

bool Scene::haveTree()
{
  for (size_t r = 0; r < row_; r++) {
    for (size_t c = 0; c < column_; c++) {
      if (scene_[r][c])
        return true;
    }
  }
  return false;
}

bool Scene::checkTree(int row, int column)
{
  int numFriend = 0;
  if (row > 0) {
    if (scene_[row-1][column]) numFriend ++;
  }
  if (row < row_-1) {
    if (scene_[row+1][column]) numFriend ++;
  }
  if (column > 0) {
    if (scene_[row][column-1]) numFriend ++;
  }
  if (column < column_-1) {
    if (scene_[row][column+1]) numFriend ++;
  }
  return (numFriend >= 2) ? true : false;
}

bool Scene::addTree(int row, int column)
{
  int r, c;
  if (row < row_-1)
    r = row + 1;
  else if (row == row_-1)
    r = row - 1;
  else return false;
  
  if (column < column_-1)
    c = column + 1;
  else if (column == column_-1)
    c = column - 1;
  else return false;

  scene_[row][c] = true;
  scene_[r][column] = true;
  scene_[r][c] = true;
  return true;
}

void Scene::print()
{
  for (size_t r = 0; r < row_; r++) {
    for (size_t c = 0; c < column_; c++) {
      if (scene_[r][c])
        cout << "^";
      else
        cout << ".";
    }
    cout << "\n";
  }
}

void solve(Scene& scene)
{
  if ((scene.row_==1 || scene.column_==1) && scene.haveTree()) {
    cout << "Impossible\n";
    return;
  }
  cout << "Possible\n";
  // Add trees
  for (size_t r = 0; r < scene.row_; r++) {
    for (size_t c = 0; c < scene.column_; c++) {
      if (scene.scene_[r][c]) {
        if (! scene.checkTree(r,c))
          scene.addTree(r,c);
      }            
    }
  }
  scene.print();
  return;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int R, C;           // No. rows R and columns C: 1 ≤ R, C ≤ 100
  int T; cin >> T;    // No. test cases T: 1 ≤ T ≤ 85
  char space;         // Char representing either tree or blank space
  for (size_t t = 1; t <= T; t++) {
    cin >> R >> C;
    Scene scene(R, C);
    for (size_t r = 0; r < R; r++) {
      for (size_t c = 0; c < C; c++) {
        cin >> space;
        scene.scene_[r][c] = (space == '^') ? true : false;
      }      
    }
    cout << "Case #" << t << ": ";
    solve(scene);
  }
  return 0;
}
