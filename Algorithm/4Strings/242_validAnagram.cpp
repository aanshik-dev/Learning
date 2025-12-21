#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  bool isAnagram(string s, string t) {
    int len = s.size();
    if (len != t.size()) {
      return false;
    }
    vector<int> ch(26, 0);
    for (int i = 0; i < len; i++) {
      ch[s[i] - 'a']++;
    }
    for (int i = 0; i < len; i++) {
      if (ch[t[i] - 'a'] == 0) {
        return false;
      }
      ch[t[i] - 'a']--;
    }
    return true;
  }
};

int main() {
  string s = "ab", t = "ba";
  Solution sol;
  bool res = sol.isAnagram(s, t);
  cout << res << endl;
  return 0;
}