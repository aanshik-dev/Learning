#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  vector<int> sortedSquares(vector<int> &nums) {
    vector<int> res(nums.size());
    int l = 0, r = nums.size() - 1;
    for (int i = nums.size() - 1; i >= 0; i--) {
      if (abs(nums[l]) > abs(nums[r])) {
        res[i] = nums[l] * nums[l];
        l++;
      } else {
        res[i] = nums[r] * nums[r];
        r--;
      }
    }
    return res;
  }
};

int main() {
  vector<int> nums = {-4, -1, 0, 3, 10};
  Solution sol;
  vector<int> res = sol.sortedSquares(nums);
  for (int i : res)
    cout << i << " ";
  return 0;
}