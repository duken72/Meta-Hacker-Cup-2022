#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
using namespace std;

const int ALPHA_SIZE = 26;

struct node {
  int count;
  vector<node *> child;

  node(int _count = 0) : count(_count), child(ALPHA_SIZE, nullptr) {}

  void merge(node *n) {
    count++;
    for (int i = 0; i < ALPHA_SIZE; i++) {
      if (n->child[i] != nullptr) {
        if (child[i] == nullptr) {
          child[i] = new node();
        }
        child[i]->merge(n->child[i]);
      }
    }
  }
};

class trie {
  node *root;

  template <typename Func>
  static void walk(node *n, Func f) {
    f(n->count);
    for (int i = 0; i < ALPHA_SIZE; i++) {
      if (n->child[i] != nullptr) {
        walk(n->child[i], f);
      }
    }
  }

  static void clean_up(node *n) {
    for (int i = 0; i < ALPHA_SIZE; i++) {
      if (n->child[i] != nullptr) {
        clean_up(n->child[i]);
      }
    }
    delete n;
  }

 public:
  trie() : root(new node()) {}
  ~trie() { clean_up(root); }
  void merge(node *n) { root->merge(n); }

  template <typename Func>
  void walk(Func f) const {
    walk(root, f);
  }
};

long long solve() {
  int N, p;
  char c;
  cin >> N;
  vector<vector<node>> tries(N);
  for (int i = 0, M; i < N; i++) {
    cin >> M;
    auto &T = tries[i];
    T.resize(M);
    for (int j = 1; j < M; j++) {
      cin >> p >> c;
      // if (M >= 998500) continue;
      // cout << j << "/" << M << endl;
      T[--p].child[c - 'a'] = &T[j];
    }
  }
  trie merged;
  for (auto &T : tries) {
    merged.merge(&T[0]);
  }
  auto n_choose_3 = [](long long n) {
    return n < 3 ? 0 : n * (n - 1) * (n - 2) / 6;
  };
  long long ans = 0;
  merged.walk([&](int k) {
    // This node is in k tries. For how many out of all N choose 3 possible
    // triples (T1, T2, T3) of tries is this node in at least one of the tries?
    // The answer is N choose 3 minus the number of triples that doesn't have
    // this node in any of the three tries, equal to (N - k) choose 3.
    ans += n_choose_3(N) - n_choose_3(N - k);
  });
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
    cout << "Case #" << t << ": " << solve() << endl;
  return 0;
}
// Time t = 6.5[s], failed 1 case (Out of RAM)