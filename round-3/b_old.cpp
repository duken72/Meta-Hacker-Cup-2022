// Correct, but not fast enough
#include <iostream>
#include <vector>

const int ALPHABET_SIZE = 26;

using std::cout, std::cin, std::endl;
using std::vector, std::string;
using LL = unsigned long long;

// Combinatorial: n choose 3
template <typename T>
T nC3(T n) { return (n < 3) ? 0 : n*(n-1)*(n-2) / 6; }

struct Node {
    LL count_;
    vector<Node*> child;
    Node(LL count = 0) : count_(count), child(ALPHABET_SIZE, nullptr) {}
};

class Trie
{
    Node* root;

    static void clean_up(Node* node) {
        for (size_t i = 0; i < ALPHABET_SIZE; i++) {
            if (node->child[i] != nullptr)
                clean_up(node->child[i]);
        }
        delete node;
    }
    static int char2Id(char c) { return c - 'a'; }

    void update(Node* node, string str) {
        if (str == "") {
            node->count_++;
            return;
        }
        int id = char2Id(str[0]);
        if (str.size() == 1) {
            if (node->child[id] == nullptr) {
                node->child[id] = new Node(1);
                return;
            } else {
                node->child[id]->count_++;
                return;
            }
        }
        return update(node->child[id], str.substr(1));
    }

    template <typename Func>
    static void walk(Node *n, Func f) {
        f(n->count_);
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (n->child[i] != nullptr)
                walk(n->child[i], f);
        }
    }

public:
    Trie() :    root(new Node()) {}
    ~Trie() { clean_up(root); }
    void update(const string& str) { update(root, str); };

    template <typename Func>
    void walk(Func f) const {
        walk(root, f);
    }
};


LL solve()
{
    int N; cin >> N;        // No. tries 3 ≤ N ≤ 100
    char C;                 // Edge label Cij ∈ {'a',...,'z'}
    Trie trie;
    for (int n = 0, M; n < N; n++) {
        cin >> M;                   // No. nodes 1 ≤ M ≤ 1e6
        vector<string> trie_i(M);
        trie.update("");            // Cause loop starts at m = 1
        for (size_t m = 1, P; m < M; m++) {
            cin >> P >> C; P--;     // Index of parent 1 ≤ P < j
            trie_i[m] = trie_i[P] + C;
            trie.update(trie_i[m]);
        }
    }
    LL result = 0;
    trie.walk([&](LL k) {
        result += nC3(N) - nC3(N-k);
    });
    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;        // No. test case T: 1 ≤ T ≤ 100
    for (size_t t = 1; t <= T; t++)
        cout << "Case #" << t << ": " << solve() << endl;
    return 0;
}
