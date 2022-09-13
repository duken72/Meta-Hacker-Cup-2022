#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

enum BLOCKTYPE {EMPTY, TREE, ROCK};

class Scene
{
public:
  int row_;
  int column_;
  std::vector<std::vector<BLOCKTYPE>> scene_;

  Scene(int row, int column);
  bool haveTree();
  bool haveFriends(int row, int column);
  int countPossibleFriends(int row, int column);
  std::vector<std::vector<int>> findBadTrees();
};

Scene::Scene(int row, int column)
{
  row_ = row;
  column_ = column;
  std::vector<std::vector<BLOCKTYPE>> scene(row, 
      std::vector<BLOCKTYPE>(column, BLOCKTYPE::EMPTY));
  scene_ = scene;
}

bool Scene::haveTree()
{
  for (size_t r = 0; r < row_; r++) {
    for (size_t c = 0; c < column_; c++) {
      if (scene_[r][c] == BLOCKTYPE::TREE) {
        return true;
      }
    }
  }
  return false;
}

bool Scene::haveFriends(int row, int column)
{
  int numFriend = 0;
  if (row > 0) {
    if (scene_[row-1][column] == BLOCKTYPE::TREE) numFriend ++;
  }
  if (row < row_-1) {
    if (scene_[row+1][column] == BLOCKTYPE::TREE) numFriend ++;
  }
  if (column > 0) {
    if (scene_[row][column-1] == BLOCKTYPE::TREE) numFriend ++;
  }
  if (column < column_-1) {
    if (scene_[row][column+1] == BLOCKTYPE::TREE) numFriend ++;
  }
  if (numFriend >= 2) return true;
  return false;
}

int Scene::countPossibleFriends(int row, int column)
{
  int numPotentialFriend = 0;
  if (row > 0) {
    if (scene_[row-1][column] != BLOCKTYPE::ROCK) numPotentialFriend ++;
  }
  if (row < row_-1) {
    if (scene_[row+1][column] != BLOCKTYPE::ROCK) numPotentialFriend ++;
  }
  if (column > 0) {
    if (scene_[row][column-1] != BLOCKTYPE::ROCK) numPotentialFriend ++;
  }
  if (column < column_-1) {
    if (scene_[row][column+1] != BLOCKTYPE::ROCK) numPotentialFriend ++;
  }
  return numPotentialFriend;
}

std::vector<std::vector<int>> Scene::findBadTrees()
{
  std::vector<std::vector<int>> countFriends(row_, std::vector<int>(column_, 0));

  for (size_t r = 0; r < row_; r++) {
    for (size_t c = 0; c < column_; c++) {
      if (scene_[r][c] != BLOCKTYPE::ROCK) {
        countFriends[r][c] = this->countPossibleFriends(r,c);
      }      
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
  std::ifstream myfileI ("second_second_friend_sample_input.txt");
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
      
      // Read scene
      Scene scene(R, C);
      for (size_t r = 0; r < R; r++) {
        std::getline (myfileI,line);
        for (size_t c = 0; c < C; c++) {
          if (line[c] == '^') {
            scene.scene_[r][c] = BLOCKTYPE::TREE;
          } else if (line[c] == '#') {
            scene.scene_[r][c] = BLOCKTYPE::ROCK;
          }          
        }
      }

      // Simple imposible scene
      if ((R==1 || C==1) && scene.haveTree()) {
        myfileO << "Case #" << t+1 << ": Impossible\n";
        continue;
      }

      // Check if there is a "bad" tree
      bool hasBadTree = false;
      std::vector<std::vector<int>> badTrees = scene.findBadTrees();
      for (size_t r = 0; r < scene.row_; r++) {
        for (size_t c = 0; c < scene.column_; c++) {
          if (scene.scene_[r][c] == BLOCKTYPE::TREE) {
            if (badTrees[r][c] == 0) {
              hasBadTree = true;
            }
          }
        }
      }
      if (hasBadTree) {
        myfileO << "Case #" << t+1 << ": Impossible\n";
        continue;
      }
      
      // Now that it is possible, simply fill in all "good" trees
      myfileO << "Case #" << t+1 << ": Possible\n";
      for (size_t r = 0; r < scene.row_; r++) {
        for (size_t c = 0; c < scene.column_; c++) {
          if (scene.scene_[r][c] == BLOCKTYPE::EMPTY) {
            if (badTrees[r][c] > 1) {
              scene.scene_[r][c] = BLOCKTYPE::TREE;
            }
          }              
        }            
      }

      // Print scene
      for (size_t r = 0; r < scene.row_; r++) {
        for (size_t c = 0; c < scene.column_; c++) {
          if (scene.scene_[r][c] == BLOCKTYPE::EMPTY) {
            myfileO << ".";
          } else if (scene.scene_[r][c] == BLOCKTYPE::TREE) {
            myfileO << "^";
          } else {
            myfileO << "#";
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
