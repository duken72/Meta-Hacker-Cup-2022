#include <iostream>
#include <vector>

using std::cout, std::cin, std::endl;
using std::vector, std::string;
enum BLOCKTYPE {EMPTY, TREE, ROCK};

class Scene
{
public:
  int row_;
  int column_;
  vector<vector<BLOCKTYPE>> scene_;

  Scene(int row, int column);
  bool haveTree();
  bool haveFriends(int row, int column);
  int countPossibleFriends(int row, int column);
  vector<vector<int>> findBadTrees();
  void print();
};

Scene::Scene(int row, int column)
{
  row_ = row;
  column_ = column;
  vector<vector<BLOCKTYPE>> scene(row, vector<BLOCKTYPE>(column, EMPTY));
  scene_ = scene;
}

bool Scene::haveTree()
{
  for (size_t r = 0; r < row_; r++) {
    for (size_t c = 0; c < column_; c++) {
      if (scene_[r][c] == TREE)
        return true;
    }
  }
  return false;
}

bool Scene::haveFriends(int row, int column)
{
  int numFriend = 0;
  if (row > 0) {
    if (scene_[row-1][column] == TREE) numFriend ++;
  }
  if (row < row_-1) {
    if (scene_[row+1][column] == TREE) numFriend ++;
  }
  if (column > 0) {
    if (scene_[row][column-1] == TREE) numFriend ++;
  }
  if (column < column_-1) {
    if (scene_[row][column+1] == TREE) numFriend ++;
  }
  return (numFriend >= 2) ? true : false;
}

int Scene::countPossibleFriends(int row, int column)
{
  int output = 0;
  if (row > 0) {
    if (scene_[row-1][column] != ROCK) output ++;
  }
  if (row < row_-1) {
    if (scene_[row+1][column] != ROCK) output ++;
  }
  if (column > 0) {
    if (scene_[row][column-1] != ROCK) output ++;
  }
  if (column < column_-1) {
    if (scene_[row][column+1] != ROCK) output ++;
  }
  return output;
}

vector<vector<int>> Scene::findBadTrees()
{
  vector<vector<int>> countFriends(row_, vector<int>(column_, 0));
  for (size_t r = 0; r < row_; r++) {
    for (size_t c = 0; c < column_; c++) {
      if (scene_[r][c] != ROCK)
        countFriends[r][c] = this->countPossibleFriends(r,c);
    }
  }

  bool repeat = false;
  do {
    repeat = false;
    for (size_t r = 0; r < row_; r++) {
      for (size_t c = 0; c < column_; c++) {
        if (countFriends[r][c] == 1) {
          repeat = true;
          countFriends[r][c] = 0;
          if (r > 0) {
            if (countFriends[r-1][c] > 1) countFriends[r-1][c] --;
          }
          if (r < row_-1) {
            if (countFriends[r+1][c] > 1) countFriends[r+1][c] --;
          }
          if (c > 0) {
            if (countFriends[r][c-1] > 1) countFriends[r][c-1] --;
          }
          if (c < column_-1) {
            if (countFriends[r][c+1] > 1) countFriends[r][c+1] --;
          }
        }        
      }
    }
  } while (repeat);  
  return countFriends;
}

void Scene::print()
{
  for (size_t r = 0; r < row_; r++) {
    for (size_t c = 0; c < column_; c++) {
      if (scene_[r][c] == EMPTY)
        cout << ".";
      else if (scene_[r][c] == TREE)
        cout << "^";
      else
        cout << "#";
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

  // Check if there is a "bad" tree
  bool hasBadTree = false;
  vector<vector<int>> badTrees = scene.findBadTrees();
  for (size_t r = 0; r < scene.row_; r++) {
    for (size_t c = 0; c < scene.column_; c++) {
      if (scene.scene_[r][c] == TREE) {
        if (badTrees[r][c] == 0)
          hasBadTree = true;
      }
    }
  }
  if (hasBadTree) {
    cout << "Impossible\n";
    return;
  }  
  // Now that it is possible, simply fill in all "good" trees
  cout << "Possible\n";
  for (size_t r = 0; r < scene.row_; r++) {
    for (size_t c = 0; c < scene.column_; c++) {
      if (scene.scene_[r][c] == EMPTY) {
        if (badTrees[r][c] > 1)
          scene.scene_[r][c] = TREE;
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

  int R, C;           // No. rows R and columns C: 1 ≤ R, C ≤ 3000
  int T; cin >> T;    // No. test cases T: 1 ≤ T ≤ 80
  char space;         // Char representing either tree or blank space
  for (size_t t = 1; t <= T; t++) {
    cin >> R >> C;
    Scene scene(R, C);
    for (size_t r = 0; r < R; r++) {
      for (size_t c = 0; c < C; c++) {
        cin >> space;
        if (space == '^')
          scene.scene_[r][c] = TREE;
        else if (space == '#')
          scene.scene_[r][c] = ROCK;
      }      
    }
    cout << "Case #" << t << ": ";
    solve(scene);
  }  
  return 0;
}
