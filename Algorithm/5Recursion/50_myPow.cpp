#include <bits/stdc++.h>
using namespace std;

// class Solution {
//   public:
//   double myPow(double x, int n) {
//     if (n == 0) {
//       return 1;
//     }
//     return n > 0 ? x*myPow(x,n-1): 1/x*myPow(x,n+1);
//   }
// };

class Solution {
  public:
  double myPow(double x, long long n) {
    if (n < 0) {
      x = 1 / x;
      n = -n;
    }
    double result = 1;
    double current_product = x;
    while (n > 0) {
      if (n % 2 == 1) {
        result = result * current_product;
      }
      current_product = current_product * current_product;
      n = n / 2;
    }
    return result;
  }
};

int main() {
  double x = 2.000;
  int n = -4;
  Solution sol;
  double res = sol.myPow(x, n);
  cout << res << endl;
  return 0;
}