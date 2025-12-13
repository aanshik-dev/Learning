#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int majorityElement(vector<int> &nums) {
    int res = nums[0];
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (count == 0) {
        res = nums[i];
        count = 1;
      } else if (nums[i] == res) {
        count++;
      } else {
        count--;
      }
    }
    return res;
  }
};

int main() {
  vector<int> nums = {1, 2, 1, 2, 1, 2, 3, 2};
  Solution sol;
  int res = sol.majorityElement(nums);
  cout << res << endl;
  return 0;
}