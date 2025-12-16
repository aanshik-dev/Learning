#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int findMin(vector<int> &nums) {
    int l = 0, r = nums.size() - 1, mid;
    while (l < r) {
      mid = l + (r - l) / 2;
      if (nums[mid] > nums[r]) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return nums[l];
  }
};

int main() {
  vector<int> nums = {3, 4, 5, 6, 7, 1, 2};
  Solution sol;
  int res = sol.findMin(nums);
  cout << res << endl;
  return 0;
}