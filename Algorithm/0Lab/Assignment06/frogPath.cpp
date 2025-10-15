// LOGIC : start from 2 element and maintain dp and path array:
// dp[i] = min(dp[i-1] + nums[i], dp[i-2] + nums[i]);
// path[i] = path[i-1] + path[i-2]; if dp[i-1] == dp[i-2]
// else path[i] = path[i-1] || path[i-2]; whichever smaller

#include <iostream>
#include <vector>
using namespace std;

pair<int, int> path(vector<int> &nums) {
  vector<int> dp(nums.size(), 0);
  vector<int> path(nums.size(), 0);
  if (nums.size() >= 2) {
    dp[0] = nums[0];
    dp[1] = nums[0] + nums[1];
    path[0] = 1;
    path[1] = 1;
    for (int i = 2; i < nums.size(); i++) {
      int t1 = dp[i - 1] + nums[i];
      int t2 = dp[i - 2] + nums[i];
      int best = min(t1, t2);
      dp[i] = best;
      if (best == t1) {
        path[i] += path[i - 1];
      }
      if (best == t2) {
        path[i] += path[i - 2];
      }
    }
    return {dp[nums.size() - 1], path[nums.size() - 1]};
  } else {
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) {
      sum += nums[i];
    }
    return {sum, 1};
  }
}

int main() {

  vector<int> nums = {1, 1, 4, 2, 0, 0, 0, 0, 2, 3};
  pair<int, int> res = path(nums);
  cout << "The min cost required is: " << res.first << endl;
  cout << "The number of ways are: " << res.second << endl;

  return 0;
}