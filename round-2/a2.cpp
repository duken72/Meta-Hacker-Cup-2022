#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

// Based on the given solution
#include <chrono>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

using LL = long long;
const LL MOD = (1LL << 62) - 57;
const LL SEED = chrono::steady_clock::now().time_since_epoch().count();

// Modular arithmetics
LL add(LL a, LL b) { return (a % MOD + b % MOD) % MOD; }
LL sub(LL a, LL b) { return ((a - b) % MOD + MOD) % MOD; }

// Hash function: http://xorshift.di.unimi.it/splitmix64.c
const LL get_hash(int v) {
    unsigned long long x = v + SEED;
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return (x ^ (x >> 31)) % MOD;
}

// https://cp-algorithms.com/data_structures/segment_tree.html
template <typename T>
class segment_tree {
    static T merge(const T &a, const T &b) { return add(a, b); }
    int length;
    vector<T> values;

    void build(int id, int low, int high, const vector<T>& array) {
        if (low == high) {
            values[id] = array[low];
            return;
        }
        int mid = low + (high - low) / 2;
        build(id * 2 + 1, low, mid, array);
        build(id * 2 + 2, mid + 1, high, array);
        values[id] = merge(values[id * 2 + 1], values[id * 2 + 2]);
    }

    T query(int id, int low, int high, int tgt_low, int tgt_high) const {
        if (low == tgt_low && high == tgt_high)
            return values[id];
        int mid = low + (high - low) / 2;
        if (tgt_high <= mid)
            return query(id * 2 + 1, low, mid, tgt_low, tgt_high);
        if (tgt_low > mid)
            return query(id * 2 + 2, mid + 1, high, tgt_low, tgt_high);
        return merge(
            query(id * 2 + 1, low, mid, tgt_low, mid),
            query(id * 2 + 2, mid + 1, high, mid + 1, tgt_high)); 
    }

    void update(int id, int low, int high, int target, const T &val) {
        if (target < low || target > high)
            return;
        if (low == high) {
            values[id] = val;
            return;
        }
        int mid = low + (high - low) / 2;
        update(id * 2 + 1, low, mid, target, val);
        update(id * 2 + 2, mid + 1, high, target, val);
        values[id] = merge(values[id * 2 + 1], values[id * 2 + 2]);
    }

public:
    segment_tree(const vector<T>& array) : length(array.size()), values(4 * length) {
        build(0, 0, length - 1, array);
    }

    T query(int low, int high) const { return query(0, 0, length - 1, low, high); }
    
    void update(int id, const T &val) { update(0, 0, length - 1, id, val); }
};

int solve()
{
    int N; cin >> N;                // No. interger N: 1 ≤ N ≤ 10^6
    vector<LL> hash_value(N);
    unordered_map<LL, int> hash_ref;
    for (int i = 0, Ai; i < N; i++) {
        cin >> Ai;                  // Array element: 1 ≤ Ai ≤ 10^6
        hash_value[i] = get_hash(Ai);
        hash_ref[hash_value[i]] = Ai;
    }
    segment_tree<LL> seg_tree(hash_value);
    int result = 0;
    int Q; cin >> Q;                // No. query Q: 1 ≤ Q ≤ 10^6
    for (int i = 0, op, x, y, l, r; i < Q; i++) {
        cin >> op;
        if (op == 1) {
            cin >> x >> y;
            --x;
            hash_value[x] = get_hash(y);
            hash_ref[hash_value[x]] = y;
            seg_tree.update(x, hash_value[x]);
        } else {
            cin >> l >> r;
            --l; --r;
            if ((r - l + 1) % 2 == 0)
                continue;
            if (l == r) {
                result++;
                continue;
            }
            int m = (l + r) / 2;
            LL diff1 = sub(seg_tree.query(l, m), seg_tree.query(m + 1, r));
            LL diff2 = sub(seg_tree.query(m, r), seg_tree.query(l, m - 1));
            if (hash_ref.find(diff1) != hash_ref.end() ||
                hash_ref.find(diff2) != hash_ref.end())
                result++;
        }
    }
    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;            // No. test cases T: 1 ≤ T ≤ 85
    for (size_t t = 1; t <= T; t++)
        cout << "Case #" << t << ": " << solve() << endl;
    return 0;
}

// Time t = 6.5[s]
