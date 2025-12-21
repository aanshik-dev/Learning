#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  vector<int> plusOne(vector<int> &digits) {
    int n = digits.size();
    int carry = 1;
    for (int i = n - 1; i >= 0; i--) {
      digits[i] += carry;
      carry = digits[i] / 10;
      digits[i] %= 10;
      if (carry == 0) {
        break;
      }
    }
    if (carry) {
      digits.emplace_back(0);
      digits[0] = 1;
    }
    return digits;
  }
};

int main() {
  vector<int> nums = {9,9,9};
  Solution sol;
  vector<int> res = sol.plusOne(nums);
  for (int i : res) {
    cout << i << " ";
  }
  return 0;
}