#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
  int findMaxConsecutiveOnes(vector<int> &nums) {
    int count = 0;
    int res = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] == 1) {
        count++;
      } else {
        count = 0;
      }
      res = max(res, count);
    }
    return res;
  }
};

int main() {

  vector<int> nums = {1, 1, 0, 1, 1, 1};
  Solution sol;
  int res = sol.findMaxConsecutiveOnes(nums);
  cout << res << endl;
  return 0;
}