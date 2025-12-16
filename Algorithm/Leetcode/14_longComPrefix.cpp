#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  string longestCommonPrefix(vector<string> &strs) {
    string res = strs[0];
    int strlen = strs[0].length();
    for (int i = 0; i < strs.size(); i++) {
      while (strs[i].length() < strlen || strs[i].substr(0, strlen) != res) {
        res = res.substr(0, strlen - 1);
        strlen--;
      }
    }
    return res;
  }
};

int main() {
  vector<string> strs = {"flower", "flow", "flight"};
  Solution sol;
  string res = sol.longestCommonPrefix(strs);
  cout << res << endl;
  return 0;
}