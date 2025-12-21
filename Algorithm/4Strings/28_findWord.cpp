#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int strStr(string haystack, string needle) {
    for (int i = 0; i <= (int)(haystack.size() - needle.size()); i++) {
      if (haystack.substr(i, needle.size()) == needle) {
        return i;
      }
    }
    return -1;
  }
};

int main() {
  string haystack = "aaa", needle = "aaaa";
  Solution sol;
  int res = sol.strStr(haystack, needle);
  cout << res << endl;
  return 0;
}