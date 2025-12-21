#include <bits/stdc++.h>
using namespace std;

// class Solution {
//   public:
//   int findPeakElement(vector<int> &nums) {
//     int l = 0, r = nums.size() - 1, mid;
//     while (l < r) {
//       mid = l + (r - l) / 2;
//       if ((mid > 0 ? nums[mid] > nums[mid - 1] : 1) && (mid < nums.size() - 1 ? nums[mid] > nums[mid + 1] : 1)) {
//         return mid;
//       } else if ((mid > 0 ? nums[mid] > nums[mid - 1] : 1) && (mid < nums.size() - 1 ? nums[mid + 1] > nums[mid] : 1)) {
//         l = mid + 1;
//       } else if ((mid > 0 ? nums[mid] < nums[mid - 1] : 1) && (mid < nums.size() - 1 ? nums[mid + 1] < nums[mid] : 1)) {
//         r = mid;
//       } else {
//         l = mid + 1;
//       }
//     }
//     return l;
//   }
// };

class Solution {
  public:
  int findPeakElement(vector<int> &nums) {
    int l = 0, r = nums.size() - 1;
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (nums[mid] < nums[mid + 1]) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return l;
  }
};

int main() {
  vector<int> nums = {1, 2, 3, 2, 1, 3, 6, 9, 9, 15};
  Solution sol;
  int res = sol.findPeakElement(nums);
  cout << res << endl;
  return 0;
}