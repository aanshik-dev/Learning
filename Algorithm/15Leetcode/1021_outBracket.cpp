#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  string removeOuterParentheses(string s) {
    int count = 0;
    string res = "";
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '(') {
        count++;
        if (count != 1) {
          res.append("(");
        }
      } else if (s[i] == ')') {
        count--;
        if (count != 0) {
          res.append(")");
        }
      }
    }
    return res;
  }
};

int main() {
  string str = "(()())(())";
  Solution sol;
  string res = sol.removeOuterParentheses(str);
  cout << res << endl;
  return 0;
}