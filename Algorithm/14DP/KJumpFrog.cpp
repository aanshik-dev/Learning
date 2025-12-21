#include <bits/stdc++.h>
using namespace std;

int main() {

  vector<int> nums = {2, 4, 3, 7, 4, 2, 7};
  int k = 0;
  int sol = 0;
  vector<int> dp(nums.size(), 0);
  if (k > 0 && k <= nums.size()) {
    for (int i = 1; i <= k; i++) {
      dp[i] = nums[i] - nums[0];
    }
    for (int i = k + 1; i < nums.size(); i++) {
      int minimum = INT_MAX;
      for (int j = 1; j <= k; j++) {
        minimum = min(minimum, abs(nums[i] - nums[i - j]) + dp[i - j]);
      }
      dp[i] = minimum;
    }
    sol = dp[nums.size() - 1];
  } else if (k == 0) {
    sol = -1;
  } else {
    sol = nums[nums.size() - 1] - nums[0];
  }

  cout << sol << endl;

  return 0;
}