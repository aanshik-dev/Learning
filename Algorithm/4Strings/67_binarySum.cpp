#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  string addBinary(string a, string b) {
    int i = a.size() - 1;
    int j = b.size() - 1;
    string res;
    int carry = 0;
    while (i >= 0 || j >= 0 || carry) {
      if (i >= 0) {
        carry += a[i--] - '0';
      }
      if (j >= 0) {
        carry += b[j--] - '0';
      }
      res += carry % 2 + '0';
      carry /= 2;
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

int main() {
  string a = "1111", b = "1";
  Solution sol;
  string res = sol.addBinary(a, b);
  cout << res << endl;
  return 0;
}