#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
  int numSubsetSum(vector<int> &arr, int i, int target, vector<vector<int>> &dp) {
    if (target == 0)
      return 1;
    if (i == arr.size())
      return 0;
    if (dp[i][target] != -1)
      return dp[i][target];
    int notake = numSubsetSum(arr, i + 1, target, dp);
    int take = 0;
    if (arr[i] <= target)
      take = numSubsetSum(arr, i + 1, target - arr[i], dp);
    dp[i][target] = take + notake;
    return dp[i][target];
  }

  public:
  int tabular(vector<int> &arr, int target) {
    int n = arr.size();
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
    for (int i = 0; i <= n; i++)
      dp[i][0] = 1;
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 1; j <= target; j++) {
        int notake = dp[i + 1][j];
        int take = 0;
        if (arr[i] <= j)
          take = dp[i + 1][j - arr[i]];
        dp[i][j] = take + notake;
      }
    }
    return dp[0][target];
  }
};
int main() {
  vector<int> nums = {2, 3, 5, 16, 8, 10};
  Solution sol;
  int trgt = 10;
  vector<vector<int>> dp(nums.size() + 1, vector<int>(trgt + 1, -1));
  int res = sol.numSubsetSum(nums, 0, trgt, dp);
  cout << res << endl;
  int res2 = sol.tabular(nums, trgt);
  cout << res2 << endl;
  return 0;
}