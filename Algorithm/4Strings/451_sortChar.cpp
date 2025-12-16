#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  string frequencySort(string s) {
    unordered_map<char, int> m;
    for (char c : s) {
      m[c]++;
    }
    vector<pair<char, int>> v(m.begin(), m.end());
    sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
      return a.second > b.second;
    });
    s.clear();
    for (auto p : v) {
      s.append(p.second, p.first);
    }
    return s;
  }
};

int main() {
  string s = "Aabb";
  Solution sol;
  string res = sol.frequencySort(s);
  cout << res << endl;
  return 0;
}