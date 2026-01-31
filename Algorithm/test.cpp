#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int closestNumber(int n, int m) {
    int mod = n % m;
    if (mod > 0) {
      if (mod < abs(m / 2)) {
        return n - mod;
      } else {
        return n + abs(m) - mod;
      }
    } else {
      if (abs(mod) < abs(m / 2)) {
        return n + abs(mod);
      } else {
        return n - (abs(m) + mod);
      }
    }
  }
};

int main() {
  Solution sol;
  int res = sol.closestNumber(45,50);
  cout << res << endl;
  return 0;
}

// -15 6 -18
// 10 4 12
// 20 5 20