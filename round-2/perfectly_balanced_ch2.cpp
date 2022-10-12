#include <chrono>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

using LL = long long;
const LL MOD = (1LL << 62) - 57;
const LL SEED = chrono::steady_clock::now().time_since_epoch().count();

const LL get_hash(int v) {
  unsigned long long x = v + SEED;
  // http://xorshift.di.unimi.it/splitmix64.c
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return (x ^ (x >> 31)) % MOD;
}

LL add(LL a, LL b) { return (a % MOD + b % MOD) % MOD; }
LL sub(LL a, LL b) { return ((a - b) % MOD + MOD) % MOD; }

template <typename T>
class segment_tree {
  static T join_values(const T &a, const T &b) { return add(a, b); }
  static T join_value_with_delta(const T &v, const T &d) { return d; }

  int len;
  vector<T> value;

  template <typename It>
  void build(int i, int lo, int hi, It arr) {
    if (lo == hi) {
      value[i] = *(arr + lo);
      return;
    }
    int mid = lo + (hi - lo) / 2;
    build(i * 2 + 1, lo, mid, arr);
    build(i * 2 + 2, mid + 1, hi, arr);
    value[i] = join_values(value[i * 2 + 1], value[i * 2 + 2]);
  }

  T query(int i, int lo, int hi, int tgt_lo, int tgt_hi) const {
    if (lo == tgt_lo && hi == tgt_hi) {
      return value[i];
    }
    int mid = lo + (hi - lo) / 2;
    if (tgt_lo <= mid && mid < tgt_hi) {
      return join_values(
          query(i * 2 + 1, lo, mid, tgt_lo, min(tgt_hi, mid)),
          query(i * 2 + 2, mid + 1, hi, max(tgt_lo, mid + 1), tgt_hi));
    }
    if (tgt_lo <= mid) {
      return query(i * 2 + 1, lo, mid, tgt_lo, min(tgt_hi, mid));
    }
    return query(i * 2 + 2, mid + 1, hi, max(tgt_lo, mid + 1), tgt_hi);
  }

  void update(int i, int lo, int hi, int target, const T &d) {
    if (target < lo || target > hi) {
      return;
    }
    if (lo == hi) {
      value[i] = join_value_with_delta(value[i], d);
      return;
    }
    int mid = lo + (hi - lo) / 2;
    update(i * 2 + 1, lo, mid, target, d);
    update(i * 2 + 2, mid + 1, hi, target, d);
    value[i] = join_values(value[i * 2 + 1], value[i * 2 + 2]);
  }

 public:
  template <typename It>
  segment_tree(It lo, It hi) : len(hi - lo), value(4 * len) {
    build(0, 0, len - 1, lo);
  }

  int size() const { return len; }
  T at(int i) const { return query(i, i); }
  T query(int lo, int hi) const { return query(0, 0, len - 1, lo, hi); }
  void update(int i, const T &d) { update(0, 0, len - 1, i, d); }
};

int solve() {
  int N;
  cin >> N;
  vector<LL> hval(N);
  unordered_map<LL, int> hrev;
  for (int i = 0, a; i < N; i++) {
    cin >> a;
    hval[i] = get_hash(a);
    hrev[hval[i]] = a;
  }
  segment_tree<LL> ST(hval.begin(), hval.end());
  int Q;
  cin >> Q;
  int ans = 0;
  for (int i = 0, op, x, y, l, r; i < Q; i++) {
    cin >> op;
    if (op == 1) {
      cin >> x >> y;
      hval[--x] = get_hash(y);
      hrev[hval[x]] = y;
      ST.update(x, hval[x]);
    } else {
      cin >> l >> r;
      --l, --r;
      if ((r - l + 1) % 2 == 0) {
        continue;
      }
      if (l == r) {
        ans++;
        continue;
      }
      int m = (l + r) / 2;
      LL diff1 = sub(ST.query(l, m), ST.query(m + 1, r));
      LL diff2 = sub(ST.query(m, r), ST.query(l, m - 1));
      if (hrev.find(diff1) != hrev.end() || hrev.find(diff2) != hrev.end()) {
        ans++;
      }
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    cout << "Case #" << t << ": " << solve() << endl;
  }
  return 0;
}
