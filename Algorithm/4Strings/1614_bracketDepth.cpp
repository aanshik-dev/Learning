#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int maxDepth(string s) {
    int count = 0, m = 0;
    for (char c : s) {
      if (c == '(') {
        count++;
      } else if (c == ')') {
        count--;
      }
      m = max(m, count);
    }
    return m;
  }
};

int main() {
  string s = "(1+(2*3)+((8)/4))+1";
  Solution sol;
  int res = sol.maxDepth(s);
  cout << res << endl;
  return 0;
}