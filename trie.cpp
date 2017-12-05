#include <chrono>
#include <vector>
#include <iostream>

using namespace std;
using namespace std::chrono;

const int MIN_CHAR = 32;
const int MAX_CHAR = 126;
const int ASIZE = MAX_CHAR - MIN_CHAR + 1;

struct node_t {
  vector<int> next = vector<int>(ASIZE, -1);
  bool is_term = false;
};

struct trie_t {
  vector<node_t> tree;
  const int root = 0;

  trie_t() {
    tree.emplace_back();
  }

  int char_to_int(char c) const {
    return c - MIN_CHAR;
  }

  void add(const string& s) {
    int node_id = root;
    for (char c : s) {
      const int id = char_to_int(c);
      if (tree[node_id].next[id] == -1) {
        tree[node_id].next[id] = tree.size();
        tree.emplace_back();
      }
      node_id = tree[node_id].next[id];
    }
    tree[node_id].is_term = true;
  }

  bool check(const string& s, int start) {
    int node_id = root;
    for (size_t i = start; i < s.length(); ++i) {
      const int id = char_to_int(s[i]);
      if (tree[node_id].next[id] == -1)
        return false;
      node_id = tree[node_id].next[id];
      if (tree[node_id].is_term)
        return true;
    }
    return false;
  }
};

int main() {
  auto start = high_resolution_clock::now();

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  string buf;
  getline(cin, buf);
  trie_t trie;
  for (int i = 0; i < n; ++i) {
    getline(cin, buf);
    trie.add(buf);
  }

  while (getline(cin, buf)) {
    for (size_t start = 0; start < buf.length(); ++start) {
      if (trie.check(buf, start)) {
        cout << buf << endl;
        break;
      }
    }
  }

  cerr << "Total execution time : " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << " ms" << endl;

  return 0;
}
