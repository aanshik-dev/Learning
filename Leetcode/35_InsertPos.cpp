#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int searchInsert(vector<int> &nums, int target) {
    int start = 0, end = nums.size() - 1, mid = 0;
    while (start <= end) {
      mid = start + (end - start) / 2;
      if (nums[mid] == target) {
        return mid;
      } else if (nums[mid] < target) {
        start = mid + 1;
      } else {
        end = mid - 1;
      }
    }
    return start;
  }
};

int main() {
  vector<int> nums = {1, 3, 5, 6, 7, 9, 12, 15, 18, 20};
  Solution sol;
  int res = sol.searchInsert(nums, 3);
  cout << res << endl;
  return 0;
}

// 1, 3, 5, 6, |7|, 9, 12, |15|, 18, 20