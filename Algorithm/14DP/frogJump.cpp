#include <bits/stdc++.h>
using namespace std;

int minEnergy(vector<int> &nums, vector<int> &dp, int stair) {
  if (stair == 0)
    return 0;
  else if (stair == 1) {
    return abs(nums[1] - nums[0]);
  }
  if (dp[stair] != -1)
    return dp[stair];
  dp[stair] = min(minEnergy(nums, dp, stair - 1) + abs(nums[stair] - nums[stair - 1]), minEnergy(nums, dp, stair - 2) + abs(nums[stair] - nums[stair - 2]));
  return dp[stair];
}

int main() {

  vector<int> nums = {10, 20, 30, 10};
  int prev2 = 0;
  int prev1 = abs(nums[1] - nums[0]);
  int cur = prev1;
  for (int i = 2; i < nums.size(); i++) {
    cur = min(abs(nums[i] - nums[i - 1]) + prev1, abs(nums[i] - nums[i - 2]) + prev2);
    prev2 = prev1;
    prev1 = cur;
  }
  cout << "Using Bottom Up (Loop) approach: " << cur << endl;

  vector<int> dp(nums.size() + 1, -1);

  int sol = minEnergy(nums, dp, nums.size() - 1);
  cout << "Using Top Down (Memoization) approach: " << sol << endl;

  return 0;
}