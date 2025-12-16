// Number of Subarray Sum Equals K
#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
  int subarraySum(vector<int> &nums, int k) {
    int i = 0, j = 0, sum = 0, count = 0;
    while (j < nums.size()) {
      sum += nums[j];
      if (sum == k)
        count++;
      while (sum >= k) {
        sum -= nums[i];
        if (sum == k)
          count++;
        i++;
      }
      j++;
    }
    return count;
  }
};

int main() {
  Solution sol;
  int k = 0;
  vector<int> nums = {1, -1, 1, -1};
  int res = sol.subarraySum(nums, k);
  cout << res;
  return 0;
}