#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
  int climbStairs(int n) {
    if (n <= 1)
      return n;
    int cur = 2;
    int prev = 2;
    int prev2 = 1;
    for (int i = 3; i <= n; i++) {
      cur = prev + prev2;
      prev2 = prev;
      prev = cur;
    }
    return cur;
  }
};

int main() {
  int n;
  cin >> n;

  Solution s;
  cout << s.climbStairs(n);

  return 0;
}