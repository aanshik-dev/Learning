#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  bool check(vector<int> &nums) {
    int count = 0;
    for (int i = 1; i < nums.size(); i++) {
      if (nums[i] < nums[i - 1]) {
        if (count >= 1)
          return false;
        count++;
      }
    }
    if (count == 1 && nums[0] < nums[nums.size() - 1])
      return false;
    return true;
  }
};

int main() {
  Solution sol;
  vector<int> nums = {1};
  bool res = sol.check(nums);
  cout << res << endl;
  return 0;
}
