#include <iostream>
#include <vector>
#include <string>
#include <utility>    // std::pair
#include <algorithm>  // std::find

const int DEBUG_LEVEL = 2;
#include "log.hpp"

using std::cout, std::cin, std::endl;
using std::vector, std::string, std::pair, std::find;
using LL = unsigned long long;
using Hash = pair<LL, LL>;

// String hashing
const int P1 = 31, M1 = 1e9 + 7;
const int P2 = 37, M2 = 1e9 + 9;
const int P = 29791; // 111111
// String hash: polynomial rolling hash function
// Hash hashString(const string& str)
// {
//   LL hash1 = 0, hash2 = 0, pow1 = 1, pow2 = 1;
//   for (char c : str) {
//     hash1 = (hash1 + (c + 1 - 'a') * pow1)%M1;
//     pow1 = (pow1 * P1)%M1;
//     hash2 = (hash2 + (c + 1 - 'a') * pow2)%M2;
//     pow2 = (pow2 * P2)%M2;
//   }  
//   return pair<LL, LL>(hash1, hash2);
// }
int hashString(const string& str)
{
  int hash = 0, pow = 1;
  for (char c : str) {
    hash = (hash + (c + 1 - 'a') * pow)%M2;
    pow = (pow * P2)%M2;
  }
  return hash;
}

struct Trie
{
  int M;  // No. nodes
  vector<int> parents;
  vector<string> nodeStrings;

  Trie(int nodes)
  : M(nodes), parents(nodes, 0), nodeStrings(nodes) {}

  void add_node(int idNode, int idParent, char edge) {
    parents[idNode] = idParent;
    nodeStrings[idNode] = nodeStrings[idParent] + string(1, edge);
  }
};
// ostream & operator << (ostream& os, const Trie& trie)
// {
//   cout << "Trie:\n";
//   for(auto elem : trie.parents)
//     os << elem << " ";
//   cout << endl;
//   for(auto elem : trie.nodeStrings)
//     os << elem << " ";
//   cout << endl;
//   return os;
// }

// TODO: improve here, factorial table wouls help
// Combinatorial: n choose k
unsigned int nCk(unsigned int n, unsigned int k) {
  if ((n == 0) || (k > n)) return 0;
  if (k * 2 > n) k = n - k;
  if (k == 0) return 1;
  int result = n;
  for (int i = 2; i <= k; ++i)
    result = result * (n-i+1) / i;
  return result;  
}
// Combinatorial: n choose 3
unsigned int nC3(unsigned int n, unsigned int k) {
  return (n < 3) ? 0 : n*(n-1)*(n-2)/6;
}

// int get_combinatorial(int N, int K)

int solve()
{
  int N; cin >> N;    // No. tries 3 ≤ N ≤ 100
  vector<Trie> tries; // Vector of tries
  int Mi;             // No. nodes 1 ≤ Mi ≤ 1e6
  int Pij;            // Index of parent 1 ≤ Pij < j
  char Cij;           // Label of the edge Cij ∈ {'a',...,'z'}
  // vector<int> hash_table(M2, 0);
  // vector<int> uniqueHash;
  for (int n = 0; n < N; n++) {
    cin >> Mi;
    Trie trie_i(Mi);
    for (size_t m = 1; m < Mi; m++) {
      cin >> Pij >> Cij; Pij--;
      trie_i.add_node(m, Pij, Cij);
    }
    tries.push_back(trie_i);
  }
  // for (auto trie : tries)
  //   cout << trie;
  

  // TODO: Count how many tries include a certain string?

  vector<string> uniqueStrings;
  vector<LL> counts;
  for (Trie trie_i : tries) {
    for (string s : trie_i.nodeStrings) {
      auto it = find(uniqueStrings.begin(), uniqueStrings.end(), s);
      if (it != uniqueStrings.end())
        counts[it-uniqueStrings.begin()] = counts[it-uniqueStrings.begin()] + 1;
      else {
        uniqueStrings.push_back(s);
        counts.push_back(1);
      }      
    }
  }
  // cout << "Hashing" << endl;
  // for (Trie trie_i : tries) {
  //   for (string s : trie_i.nodeStrings) {
  //     LOGIF(2, s, " ", hashString(s));
  //     if (hash_table[hashString(s)] == 0)
  //       uniqueHash.push_back(hashString(s));
  //     else
  //       hash_table[hashString(s)] = hash_table[hashString(s)] + 1;
  //   }
  // }
  // for (auto hash : uniqueHash)
  //   counts.push_back(hash_table[hash]);  

  if (N <= 3)
    return counts.size();
  int output = counts.size() * nCk(N, 3);
  // LOGIF(2, "\n", uniqueStrings, counts);
  // LOGIF(2, "nCk(", N, ",3)=", nCk(N, 3), " ", counts.size(), " out=", output);

  for (int i : counts)
    output -= nCk(N-i, 3);
    // LOGIF(2, N-i, " nCk(N-i, 3)=", nCk(N-i, 3));
  return output;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T; cin >> T;    // No. test case T: 1 ≤ T ≤ ??
  for (size_t t = 1; t <= T; t++) {
    // if (t > 5) {
    //   cout << "Case #" << t << ": " << 0 << endl;
    // } else {
    //   cout << "Case #" << t << ": " << solve() << endl;
    // }
    cout << "Case #" << t << ": " << solve() << endl;
  }
  // cout << M1 << endl;
  // Hash d = hashString("duke7295");
  // cout << d.first << " " << d.second << endl;
  // Hash p = hashString("phanh1802");
  // cout << p.first << " " << p.second << endl;
  return 0;
}
