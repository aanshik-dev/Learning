#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int rob(vector<int> &nums) {
    int n = nums.size();
    if (n >= 2) {
      nums[1] = max(nums[0], nums[1]);
    }
    for (int i = 2; i < n; i++) {
      nums[i] = max(nums[i - 1], nums[i - 2] + nums[i]);
    }
    return n == 0 ? 0 : nums[n - 1];
  }
};

int main() {
  vector<int> nums = {2, 7, };
  Solution sol;
  int res = sol.rob(nums);
  cout << res << endl;
  return 0;
}