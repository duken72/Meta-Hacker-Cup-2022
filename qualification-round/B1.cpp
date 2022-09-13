#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// It would be impossible for the trees to have 2 friends,
// if the width or height of the painting is 1, unless there
// is no tree.
// 
// Otherwise, it is always possible, simply add trees to all
// positions would work. But a less overkill approach would
// be create 2x2 blocks of trees

class Scene
{
public:
  int row_;
  int column_;
  std::vector<std::vector<bool>> scene_;

  Scene(int row, int column);
  bool haveTree();
  bool checkTree(int row, int column);
  bool addTree(int row, int column);
};

Scene::Scene(int row, int column)
{
  row_ = row;
  column_ = column;
  std::vector<bool> boolCol(column, false);
  std::vector<std::vector<bool>> scene(row, boolCol);
  scene_ = scene;
}

bool Scene::haveTree()
{
  for (size_t r = 0; r < row_; r++) {
    for (size_t c = 0; c < column_; c++) {
      if (scene_[r][c]) {
        return true;
      }
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
  if (numFriend >= 2) return true;
  return false;
}

bool Scene::addTree(int row, int column)
{
  int r, c;
  if (row < row_-1) {
    r = row + 1;
  } else if (row == row_-1) {
    r = row - 1;
  } else return false;
  
  if (column < column_-1) {
    c = column + 1;
  } else if (column == column_-1) {
    c = column - 1;
  } else return false;

  scene_[row][c] = true;
  scene_[r][column] = true;
  scene_[r][c] = true;
  return true;
}

std::vector<int> stringToVector(std::string str)
{
  std::stringstream iss(str);
  int number;
  std::vector<int> outVect;
  while ( iss >> number )
    outVect.push_back(number);
  return outVect;
}


int main()
{
  std::ifstream myfileI ("second_friend_input.txt");
  std::ofstream myfileO ("output.txt", std::ios::trunc);
  // T: number of test cases
  // R: number of row
  // C: number of column
  int T, R, C;

  if (myfileI.is_open() && myfileO.is_open()) {
    std::string line;
    std::getline (myfileI,line);
    T = stoi(line);
    
    // Loop over each test case
    for (size_t t = 0; t < T; t++) {
      std::getline (myfileI,line);
      std::vector<int> vectIn = stringToVector(line);
      R = vectIn[0];
      C = vectIn[1];
      Scene scene(R, C);
      
      // Read scene
      for (size_t r = 0; r < R; r++) {
        std::getline (myfileI,line);
        for (size_t c = 0; c < C; c++) {
          if (line[c] == '^') {
            scene.scene_[r][c] = true;
          } else {
            scene.scene_[r][c] = false;
          }
        }
      }

      // Impossible scene
      if ((R==1 || C==1) && scene.haveTree()) {
        myfileO << "Case #" << t+1 << ": Impossible\n";
        continue;
      }

      // Possible scene
      myfileO << "Case #" << t+1 << ": Possible\n";        
      for (size_t r = 0; r < scene.row_; r++) {
        for (size_t c = 0; c < scene.column_; c++) {
          if (scene.scene_[r][c]) {
            if (! scene.checkTree(r,c)) {
              scene.addTree(r,c);
            }
          }              
        }            
      }

      // scene.printScene();
      for (size_t r = 0; r < scene.row_; r++) {
        for (size_t c = 0; c < scene.column_; c++) {
          if (scene.scene_[r][c]) {
            myfileO << "^";
          } else {
            myfileO << ".";
          }
        }
        myfileO << "\n";
      }
    }
    myfileI.close();
    myfileO.close();
  } else std::cout << "Unable to open file for reading";
  
  return 0;
}
