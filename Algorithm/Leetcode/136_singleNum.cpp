#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int singleNumber(vector<int> &nums) {
    int res = 0;
    for (int i = 0; i < nums.size(); i++) {
      res ^= nums[i];
    }
    return res;
  }
};

int main() {
  vector<int> nums = {1, 1, 3, 3, 6, 4, 4};
  Solution sol;
  int res = sol.singleNumber(nums);
  cout << res << endl;
  return 0;
}