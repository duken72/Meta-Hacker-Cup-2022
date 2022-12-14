#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <array>
#include <vector>

using namespace std;
const char EMPTY = '.', TREE = '^';

#define USE_ARRAY true
#if USE_ARRAY
const int S = 100;
array<array<char, S>, S> scene_;
#endif

struct Scene {
    int row_;
    int column_;

#if USE_ARRAY
    Scene(int row, int column) : row_(row), column_(column) {
        scene_.fill({EMPTY});
    }
#else
    vector<vector<char>> scene_;
    Scene(int row, int column) : row_(row), column_(column),
        scene_(row, vector(column, EMPTY)) {}
#endif

    bool haveTree() const {
        for (int r = 0; r < row_; r++) {
            for (int c = 0; c < column_; c++) {
                if (scene_[r][c] == TREE)
                    return true;
            }
        }
        return false;
    }
};

void solve()
{
    int R, C;               // No. rows & columns
    cin >> R >> C;          // 1 ≤ R, C ≤ 100
    Scene scene(R, C);
    for (size_t r = 0; r < R; r++)
        for (size_t c = 0; c < C; c++)
#if USE_ARRAY
            cin >> scene_[r][c];
#else
            cin >> scene.scene_[r][c];
#endif

    bool haveTree = scene.haveTree();
    if ((scene.row_==1 || scene.column_==1) && haveTree) {
        cout << "Impossible" << endl;
        return;
    }
    cout << "Possible" << endl;
    for (size_t r = 0; r < R; r++) {
        for (size_t c = 0; c < C; c++)
            cout << (haveTree ?  TREE : EMPTY);
        cout << endl;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;                // No. test case T: 1 ≤ T ≤ 85
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
