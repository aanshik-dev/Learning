#include <iostream>
#include <vector>
using namespace std;

class Solution {

  public:
  int findMinIdx(vector<int> &nums, int start, int end) {
    if (end - start <= 1) {
      return nums[start] < nums[end] ? start : end;
    }
    if (nums[start] < nums[end]) {
      return start;
    } else {
      int mid = (start + end) / 2;
      if (nums[mid] > nums[start]) {
        return findMinIdx(nums, mid, end);
      } else {
        return findMinIdx(nums, start, mid);
      }
    }
  }

  public:
  int binarySearch(vector<int> &nums, int start, int end, int target) {
    if (end < start) {
      return -1;
    }
    int mid = (start + end) / 2;
    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] > target) {
      return binarySearch(nums, start, mid - 1, target);
    } else {
      return binarySearch(nums, mid + 1, end, target);
    }
  }

  public:
  int search(vector<int> &nums, int target) {
    int minIdx = findMinIdx(nums, 0, nums.size() - 1);
    int res = -1;
    if (minIdx > 0) {

      if (target >= nums[0]) {
        res = binarySearch(nums, 0, minIdx - 1, target);
      } else if (target >= nums[minIdx]) {
        res = binarySearch(nums, minIdx, nums.size() - 1, target);
      }
    } else {
      res = binarySearch(nums, 0, nums.size() - 1, target);
    }
    return res;
  }
};

int main() {
  Solution sol;
  vector<int> nums = {3,4,5,1,2};

  int res = sol.search(nums, 4);
  cout << res << endl;

  return 0;
}