#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int lengthOfLastWord(string s) {
    int i = s.size() - 1;
    int len = 0;
    while (i >= 0 && s[i] == ' ') {
      i--;
    }
    while (i >= 0 && s[i] != ' ') {
      len++;
      i--;
    }
    return len;
  }
};

int main() {
  string s = "abs";
  Solution sol;
  int res = sol.lengthOfLastWord(s);
  cout << res << endl;
  return 0;
}