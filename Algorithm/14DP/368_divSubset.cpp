#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  vector<int> largestDivisibleSubset(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();

    vector<int> dp(n, 1);
    vector<int> back(n, 0);
    int maxi = 0;
    int idx = 0;
    for (int i = 1; i < nums.size(); i++) {
      back[i] = i;
      for (int j = 0; j < i; j++) {
        if ((nums[i] % nums[j] == 0) && dp[i] < dp[j] + 1) {
          dp[i] = dp[j] + 1;
          back[i] = j;
        }
      }
      if (dp[i] > maxi) {
        maxi = dp[i];
        idx = i;
      }
    }
    vector<int> arr;
    arr.push_back(nums[idx]);
    while (back[idx] != idx) {
      idx = back[idx];
      arr.push_back(nums[idx]);
    }
    sort(arr.begin(), arr.end());
    return arr;
  }
};

int main() {

  vector<int> nums = {1, 2, 4, 5, 8, 9};
  Solution sol;
  vector<int> res = sol.largestDivisibleSubset(nums);
  for (int i : res) {
    cout << i << " ";
  }
  return 0;
}