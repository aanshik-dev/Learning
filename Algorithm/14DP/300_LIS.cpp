#include <bits/stdc++.h>
using namespace std;

class Solution {

  public:
  int lis(vector<int> &nums) {
    int n = nums.size();
    vector<int> seq;
    seq.push_back(nums[0]);
    for (int i = 1; i < nums.size(); i++) {
      if (nums[i] > seq.back()) {
        seq.push_back(nums[i]);
      } else {
        int idx = lower_bound(seq.begin(), seq.end(), nums[i]) - seq.begin();
        seq[idx] = nums[i];
      }
    }
    return seq.size();
  }

  // 1D Array Method along with printing
  public:
  int lis1d(vector<int> &nums) {
    int n = nums.size();
    vector<int> dp(n, 1);
    vector<int> back(n, 0);
    for (int i = 0; i < n; i++) {
      back[i] = i;
    }
    for (int i = 1; i < nums.size(); i++) {
      for (int j = 0; j < i; j++) {
        if (nums[i] > nums[j] && dp[i] < dp[j] + 1) {
          dp[i] = dp[j] + 1;
          back[i] = j;
        }
      }
    }

    int idx = 0;
    for (int i = 0; i < n; i++) {
      idx = (dp[i] > dp[idx] ? i : idx);
    }
    vector<int> arr;
    while (back[idx] != idx) {
      arr.push_back(nums[idx]);
      idx = back[idx];
    }
    arr.push_back(nums[idx]);
    reverse(arr.begin(), arr.end());
    for (auto i : arr)
      cout << i << " ";
    cout << endl;
    return *max_element(dp.begin(), dp.end());
  }

  // 2D Array Method 1 to N
  public:
  int lisTop(vector<int> &nums, int i, int prev, vector<vector<int>> &dp) {
    // Base
    if (i == nums.size()) {
      return 0;
    }
    // Recursion
    if (dp[i][prev + 1] != -1) {
      return dp[i][prev + 1];
    }
    int len = lisTop(nums, i + 1, prev, dp);
    if (prev == -1 || nums[i] > nums[prev]) {
      len = max(len, lisTop(nums, i + 1, i, dp) + 1);
    }
    return dp[i][prev + 1] = len;
  }

  // 2D Array Method N to 1
  int lisRev(vector<int> &nums, int i, int nxt, vector<vector<int>> &dp) {
    // Base
    if (i < 0) {
      return 0;
    }
    // Recursion
    if (dp[i][nxt] != -1) {
      return dp[i][nxt];
    }
    int notTake = lisRev(nums, i - 1, nxt, dp);
    int take = 0;
    if (nxt == nums.size() || nums[i] < nums[nxt]) {
      take = lisRev(nums, i - 1, i, dp) + 1;
    }
    dp[i][nxt] = max(take, notTake);
    return dp[i][nxt];
  }

  // Tabulation
  public:
  int lisTab(vector<int> &nums) {
    int n = nums.size();
    vector<int> prevDp(n + 1, 0), currDp(n + 1, 0);

    for (int i = n - 1; i >= 0; i--) {
      for (int prev = i - 1; prev >= -1; prev--) {
        int len = prevDp[prev + 1];
        if (prev == -1 || nums[i] > nums[prev]) {
          len = max(len, prevDp[i + 1] + 1);
        }
        currDp[prev + 1] = len;
      }
      prevDp = currDp;
    }
    return prevDp[0];
  }
};

int main() {
  vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
  Solution Sol;
  vector<vector<int>> dp(nums.size(), vector<int>(nums.size() + 1, -1));

  int res = Sol.lisTop(nums, 0, -1, dp);
  cout << res << endl;
  int res2 = Sol.lisRev(nums, nums.size() - 1, nums.size(), dp);
  cout << res2 << endl;
  int res3 = Sol.lisTab(nums);
  cout << res3 << endl;
  int res4 = Sol.lis1d(nums);
  cout << res4 << endl;
  int res5 = Sol.lis(nums);
  cout << res5 << endl;
  return 0;
}