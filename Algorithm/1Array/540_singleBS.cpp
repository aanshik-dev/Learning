// Single element in a sorted array
#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int singleNonDuplicate(vector<int> &nums) {
    int l = 0, r = nums.size() - 1, mid;
    while (l < r) {
      mid = l + (r - l) / 2;
      if (mid % 2 == 1) {
        if (nums[mid] == nums[mid - 1]) {
          l = mid + 1;
        } else {
          r = mid;
        }
      } else {
        if (mid < nums.size() - 1 && nums[mid] == nums[mid + 1]) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
    }
    return nums[l];
  }
};

int main() {
  vector<int> nums = {3, 3, 7, 7, 10, 11, 11};
  Solution sol;
  int res = sol.singleNonDuplicate(nums);
  cout << res << endl;
  return 0;
}