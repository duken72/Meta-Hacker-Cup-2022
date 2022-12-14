#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <set>

using namespace std;
using coords = pair<int, int>;

const char EMPTY = '.', TREE = '^', ROCK = '#';

#define USE_ARRAY true
#if USE_ARRAY
const int S = 3000;
array<array<char, S>, S> scene_;
array<array<char, S>, S> good_trees_;
array<array<int, S>, S> friend_counts;
#endif

struct Scene {
    int row_;
    int column_;
#if USE_ARRAY
    Scene(int row, int column) : row_(row), column_(column) {
        for (int r = 0; r < row_; r++) {
            for (int c = 0; c < column_; c++) {
                scene_[r][c] = EMPTY;
                good_trees_[r][c] = EMPTY;
                friend_counts[r][c] = 0;
            }      
        }
    };
#else
    vector<vector<char>> scene_;
    vector<vector<char>> good_trees_;
    vector<vector<int>> friend_counts;
    
    Scene(int row, int column) : row_(row), column_(column),
        scene_(row_, vector(column_, EMPTY)), good_trees_(scene_),
        friend_counts(row_, vector(column_, 0)) {};
#endif

    // Check if scene has tree
    bool haveTree() const {
        for (size_t r = 0; r < row_; r++) {
            for (size_t c = 0; c < column_; c++) {
                if (scene_[r][c] == TREE)
                    return true;
            }
        }
        return false;
    }

    // Find the scene with good trees
    void findGoodTrees() {
        vector<coords> badTrees;    // List of bad trees' coordinates
        for (size_t r = 0; r < row_; r++) {
            for (size_t c = 0; c < column_; c++) {
                if (scene_[r][c] == ROCK) continue;
                friend_counts[r][c] = countPossibleFriends(r, c);
                if (friend_counts[r][c] == 1)
                    badTrees.push_back(coords(r,c));
            }
        }

        while (badTrees.size() > 0) {
            vector<coords> neighbors;   // Neighboring cells of bad trees
            for (auto [r, c] : badTrees) {
                if (r > 0)
                    if (friend_counts[r-1][c] > 0)
                        neighbors.push_back(coords(r-1,c));
                if (r < row_-1)
                    if (friend_counts[r+1][c] > 0)
                        neighbors.push_back(coords(r+1,c));
                if (c > 0)
                    if (friend_counts[r][c-1] > 0)
                        neighbors.push_back(coords(r,c-1));
                if (c < column_-1)
                    if (friend_counts[r][c+1] > 0)
                        neighbors.push_back(coords(r,c+1));
                friend_counts[r][c] = 0;
                badTrees.erase(badTrees.begin());
            }
            for (auto [r, c] : neighbors)
                friend_counts[r][c]--;
            set<coords> unique_neighbors(neighbors.begin(), neighbors.end());
            for (auto [r, c] : unique_neighbors) {
                if (friend_counts[r][c] == 1)
                    badTrees.push_back(coords(r,c));
            }
        }

        // Update good_trees_
        for (size_t r = 0; r < row_; r++) {
            for (size_t c = 0; c < column_; c++) {
            if (friend_counts[r][c] > 1)
                good_trees_[r][c] = TREE;
            else if (scene_[r][c] == ROCK)
                good_trees_[r][c] = ROCK;
            }
        }
    }
    
    // Check if scene has bad trees
    bool haveBadTree() const {
        for (size_t r = 0; r < row_; r++) {
            for (size_t c = 0; c < column_; c++) {
                if (scene_[r][c] != TREE)
                    continue;
                if (good_trees_[r][c] != TREE)
                    return true;
            }
        }
        return false;
    }

    // Count possible friends
    int countPossibleFriends(int r, int c) {
        int output = 0;
        if (r > 0)              output += (scene_[r - 1][c] != ROCK);
        if (r < row_ - 1)       output += (scene_[r + 1][c] != ROCK);
        if (c > 0)              output += (scene_[r][c - 1] != ROCK);
        if (c < column_ - 1)    output += (scene_[r][c + 1] != ROCK);
        return output;
    }

    // Convert scene to string for printing
    string scene2str() const {
        string result;
        for (int r = 0; r < row_; r++) {
            for (int c = 0; c < column_; c++)
                result += good_trees_[r][c];
            result += "\n";
        }
        return result;
    }
};

string solve()
{
    int R, C;           // No. rows & columns
    cin >> R >> C;      // 1 ??? R, C ??? 3000
    Scene scene(R, C);
    for (size_t r = 0; r < R; r++) {
        for (size_t c = 0; c < C; c++)
#if USE_ARRAY
            cin >> scene_[r][c];
#else
            cin >> scene.scene_[r][c];
#endif
    }

    if (scene.row_ == 1 || scene.column_ == 1) {
        if (scene.haveTree())
            return "Impossible\n";
#if USE_ARRAY
        good_trees_ = scene_;
#else
        scene.good_trees_ = scene.scene_;
#endif
        return "Possible\n" + scene.scene2str();
    }

    scene.findGoodTrees();
    if (scene.haveBadTree())
        return "Impossible\n";
    return "Possible\n" + scene.scene2str();
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;        // No. test case T: 1 ??? T ??? 80
    for (int t = 1; t <= T; t++)
        cout << "Case #" << t << ": " << solve();
    return 0;
}
