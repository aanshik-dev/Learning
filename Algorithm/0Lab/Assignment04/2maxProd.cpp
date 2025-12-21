#include <iostream>
#include <vector>
using namespace std;
class Solution {
  public:
  int subMax(vector<int> &nums, int start, int end) {
    if (start == end) {
      return nums[start];
    }
    int mid = (start + end) / 2;
    int left = subMax(nums, start, mid);
    int right = subMax(nums, mid + 1, end);
    int leftMax = nums[mid];
    int rightMax = nums[mid + 1];
    int leftMin = nums[mid];
    int rightMin = nums[mid + 1];
    int prod = 1;
    for (int i = mid; i >= start; i--) {
      prod = prod * nums[i];
      leftMin = min(leftMin, prod);
      leftMax = max(leftMax, prod);
    }
    prod = 1;
    for (int i = mid + 1; i <= end; i++) {
      prod = prod * nums[i];
      rightMin = min(rightMin, prod);
      rightMax = max(rightMax, prod);
    }
    int crossMax = max(leftMin * rightMin, leftMax * rightMax);
    return max(max(left, right), crossMax);
  }

  public:
  int maxProduct(vector<int> &nums) {
    return subMax(nums, 0, nums.size() - 1);
  }
};

int main() {
  Solution sol;
  vector<int> nums = {2,3,-2,4};
  int res = sol.maxProduct(nums);
  cout << res << endl;
  return 0;
}