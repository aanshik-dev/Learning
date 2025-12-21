#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  bool isPalindrome(string s) {
    int k = 0;
    for (char &c : s) {
      c = tolower(c);
    }
    for (int i = 0; i < s.size(); i++) {
      if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9')) {
        s[k++] = s[i];
      }
    }
    for (int i = 0, j = k - 1; i < j; i++, j--) {
      if (s[i] != s[j]) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  string s = "A man, a plan, a canal: Panama";
  Solution sol;
  bool res = sol.isPalindrome(s);
  cout << res << endl;
  return 0;
}