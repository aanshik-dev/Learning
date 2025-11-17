#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
  bool isSubsetSum(vector<int> &arr, int i, int target, vector<vector<int>> &dp) {
    if (target == 0)
      return true;
    if (i == arr.size())
      return false;
    if (dp[i][target] != -1)
      return dp[i][target];
    bool notake = isSubsetSum(arr, i + 1, target, dp);
    bool take = false;
    if (arr[i] <= target)
      take = isSubsetSum(arr, i + 1, target - arr[i], dp);
    dp[i][target] = take || notake;
    return dp[i][target];
  }

  public:
  bool subsetSum(vector<int> &arr, int target) {
    int n = arr.size();
    // DP table: dp[i][t] = whether using first i elements we can make sum t
    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));
    // Base case: sum 0 is always possible (take no element)
    for (int i = 0; i < n; i++) {
      dp[i][0] = true;
    }
    // First element handling
    if (arr[0] <= target)
      dp[0][arr[0]] = true;
    // Fill the DP table
    for (int i = 1; i < n; i++) {
      for (int t = 1; t <= target; t++) {

        bool notTake = dp[i - 1][t];
        bool take = false;

        if (t >= arr[i])
          take = dp[i - 1][t - arr[i]];

        dp[i][t] = take || notTake;
      }
    }
    return dp[n - 1][target];
  }

  public:
  bool tabular(vector<int> &arr, int target) {
    int n = arr.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
    for (int i = 0; i <= n; i++)
      dp[i][0] = true;
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 1; j <= target; j++) {
        bool notake = dp[i + 1][j];
        bool take = false;
        if (arr[i] <= j)
          take = dp[i + 1][j - arr[i]];
        dp[i][j] = take || notake;
      }
    }
    return dp[0][target];
  }
};
int main() {
  vector<int> nums = {2, 3, 5};
  Solution sol;
  int trgt = 6;
  vector<vector<int>> dp(nums.size() + 1, vector<int>(trgt + 1, -1));
  bool res = sol.isSubsetSum(nums, 0, trgt, dp);
  cout << res << endl;
  bool res2 = sol.tabular(nums, trgt);
  cout << res2 << endl;
  return 0;
}