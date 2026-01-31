// Find the greatest number possible with the given number's digits

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int nextGreaterElement(int n) {
    vector<int> digit;
    while (n > 0) {
      digit.push_back(n % 10);
      n /= 10;
    }
    // sort
    // cout << digit[0]<< digit[1] ; 
    return 0;
  }
};

int main() {
  int n = 21;
  Solution sol;
  int res = sol.nextGreaterElement(n);
  cout << res << endl;
  return 0;
}