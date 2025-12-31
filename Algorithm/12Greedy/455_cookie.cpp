#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int findContentChildren(vector<int> &g, vector<int> &s) {
    if (s.size() == 0 || g.size() == 0)
      return 0;
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int i = 0, j = 0;
    while (i < g.size() && j < s.size()) {
      if (g[i] <= s[j])
        i++;
      j++;
    }
    return i;
  }
};

int main() {
  vector<int> g = {1, 3, 5, 9, 10};
  vector<int> s = {2, 2, 6, 8, 10};
  Solution sol;
  int res = sol.findContentChildren(g, s);
  cout << res << endl;
  return 0;
}