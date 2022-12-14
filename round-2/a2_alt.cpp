#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <chrono>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

using LL = long long;
const LL MOD = (1LL << 62) - 57;
const LL SEED = std::chrono::steady_clock::now().time_since_epoch().count();

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

// Segment tree's implementation using Node*, just longer :(
template <typename T>
struct Node {
    T value_;
    int low_, high_;
    Node<T> *left_, *right_;

    Node() : value_(0), low_(0), high_(0), left_(nullptr), right_(nullptr) {};

    Node(int low, int high, const vector<T>& array)
    : low_(low), high_(high), left_(nullptr), right_(nullptr) {
        if (low_ == high_) {
            value_ = array[low_];
            return;
        }
        int mid_ = low_ + (high_ - low_) / 2;
        left_ = new Node(low_, mid_, array);
        right_ = new Node(mid_ + 1, high_, array);
        value_ = add(left_->value_, right_->value_);
    }

    T query(int low, int high) {
        if (low == low_ && high == high_)
            return value_;
        int mid_ = low_ + (high_ - low_) / 2;
        if (high <= mid_)
            return left_->query(low, high);
        if (low > mid_)
            return right_->query(low, high);        
        return add(left_->query(low, mid_), right_->query(mid_ + 1, high));
    }

    void update(int id, T value) {
        if (id < low_ || id > high_)
            return;
        if (low_ == high_) {
            value_ = value;
            return;
        }
        left_->update(id, value);
        right_->update(id, value);
        value_ = add(left_->value_, right_->value_);
    }
};

// Segment Tree
template <typename T>
class ST {
    Node<T> *root;

    static void clean_up(Node<T>* node) {
        if (node->left_ != nullptr)
            clean_up(node->left_);
        if (node->right_ != nullptr)
            clean_up(node->right_);
        delete node;
    };
public:
    ST(const vector<T>& array) { root = new Node(0, array.size()-1, array); }
    ~ST() { clean_up(root); }

    T query(int low, int high) const { return root->query(low, high); }

    void update(int id, const T& new_value) { root->update(id, new_value); }
};

int solve()
{
    int N; cin >> N;                    // No. interger N: 1 ≤ N ≤ 10^6
    vector<LL> hash_value(N);
    unordered_map<LL, int> hash_ref;
    for (int i = 0, Ai; i < N; i++) {
        cin >> Ai;                      // Array element: 1 ≤ Ai ≤ 10^6
        hash_value[i] = get_hash(Ai);
        hash_ref[hash_value[i]] = Ai;
    }
    ST<LL> seg_tree(hash_value);
    int result = 0;
    int Q; cin >> Q;                    // No. query Q: 1 ≤ Q ≤ 10^6
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

// Time t = 7.5[s]
