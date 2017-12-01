#include <chrono>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main() {
  auto start = high_resolution_clock::now();

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;
  const int n = s.length();
  vector<int> z(n);
  z[0] = n;
  int l = -1, r = -1;
  for (int i = 1; i < n; ++i) {
    int pz = i <= r ? min(z[i - l], r - i + 1) : 0;
    while (i + pz < n && s[i + pz] == s[pz])
      ++pz;
    z[i] = pz;
    if (i + z[i] >= r) {
      l = i;
      r = i + z[i] - 1;
    }
  }

  for (int i : z)
    cout << i << " ";
  cout << endl;

  cerr << "Total execution time : " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << " ms" << endl;

  return 0;
}
