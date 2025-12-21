#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int search(vector<int> &nums, int target) {
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
    return -1;
  }
};

int main() {
  vector<int> nums = {-1};
  Solution sol;
  int res = sol.search(nums, -1);
  cout << res << endl;
  return 0;
}