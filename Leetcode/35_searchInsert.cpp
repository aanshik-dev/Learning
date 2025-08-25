#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
  int searchInsert(vector<int> &nums, int target) {
    int start = 0, end = nums.size() - 1, mid = 0;
    while (start <= end) {
      mid = (start + end) / 2;
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
  Solution sol;
  vector<int> vect = {1};

  int index = sol.searchInsert(vect, 8);
  cout << index << endl;
  return 0;
}