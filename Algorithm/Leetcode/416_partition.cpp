#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  bool canPartition(vector<int> &nums) {
    int sum = 0;
    for (int i = 0; i < nums.size(); i++)
      sum += nums[i];
    if (sum % 2 != 0)
      return false;

    int target = sum / 2;
    int n = nums.size();

    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));
    for (int i = 0; i < n; i++) {
      dp[i][0] = true;
    }
    if (nums[0] <= target)
      dp[0][nums[0]] = true;
    for (int i = 1; i < n; i++) {
      for (int t = 1; t <= target; t++) {
        bool notTake = dp[i - 1][t];
        bool take = false;
        if (t >= nums[i])
          take = dp[i - 1][t - nums[i]];
        dp[i][t] = take || notTake;
      }
    }
    return dp[n - 1][target];
  }
};

int main() {
  Solution sol;
  vector<int> nums = {1, 2, 3, 5};
  bool res = sol.canPartition(nums);
  cout << res << endl;
  return 0;
}