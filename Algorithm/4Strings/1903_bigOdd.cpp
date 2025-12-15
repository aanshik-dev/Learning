#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  string largestOddNumber(string num) {
    string res;
    for (int i = num.size() - 1; i >= 0; i--) {
      if ((num[i] - '0') % 2 == 1) {
        res = num.substr(0, i + 1);
        break;
      }
    }
    return res;
  }
};

int main() {
  string num = "521";
  Solution sol;
  string res = sol.largestOddNumber(num);
  cout << res << endl;
  return 0;
}