#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  bool isPowerOfTwo(int n) {
    return n > 0 && !(n & (n - 1));
  }
};

int main() {
  Solution sol;
  bool res = sol.isPowerOfTwo(8);
  cout << res << endl;
  return 0;
}