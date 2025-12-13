#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int reverse(int x) {
    int sol = 0;
    long num = x < 0 ? -(long)x : x;

    while (num > 0) {
      if ((sol > INT_MAX / 10) || (sol == INT_MAX / 10 && num % 10 > 7)) {
        return 0;
      }
      sol = sol * 10 + num % 10;
      num /= 10;
    }
    return x >= 0 ? sol : -sol;
  }
};

int main() {
  int num = -2147483648;
  Solution sol;
  int res = sol.reverse(num);
  cout << res << endl;
  return 0;
}