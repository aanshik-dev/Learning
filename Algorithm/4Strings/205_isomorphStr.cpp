#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  bool isIsomorphic(string s, string t) {
    unordered_map<char, char> hash;
    bool res = true;
    for (int k = 0; k < 2; k++) {
      swap(s, t);
      for (int i = 0; i < s.size(); i++) {
        if (hash.find(s[i]) != hash.end() && hash[s[i]] != t[i]) {
          res = false;
          break;
        } else {
          hash[s[i]] = t[i];
        }
      }
      hash.clear();
    }
    return res;
  }
};

class Solution {
  public:
  bool isIsomorphic(string s, string t) {
    vector<int> indexS(200, 0);
    vector<int> indexT(200, 0);
    int len = s.length();
    if (len != t.length()) {
      return false;
    }
    for (int i = 0; i < len; i++) {
      if (indexS[s[i]] != indexT[t[i]]) {
        return false;
      }
      indexS[s[i]] = i + 1;
      indexT[t[i]] = i + 1;
    }
    return true;
  }
};

int main() {
  string s = "badc", t = "baba";
  Solution sol;
  bool res = sol.isIsomorphic(s, t);
  cout << res << endl;
  return 0;
}