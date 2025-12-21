#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
  int searchMissing(vector<int> &nums, int start, int end) {
    int mid = (start + end) / 2;
    if (start > end) {
      return start + 1;
    } else if (nums[mid] == mid + 1) {
      searchMissing(nums, mid + 1, end);
    } else {
      searchMissing(nums, start, mid - 1);
    }
  }
};

main() {
  Solution sol;
  vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 10};
  int res = sol.searchMissing(nums, 0, nums.size() - 1);
  cout << res << endl;
  return 0;
}