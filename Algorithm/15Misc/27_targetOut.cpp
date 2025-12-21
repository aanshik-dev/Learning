#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int removeElement(vector<int> &nums, int val) {
    int k = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] != val) {
        swap(nums[k], nums[i]);
        k++;
      } else {
      }
    }
    return k;
  }
};

int main() {
  vector<int> nums = {1, 1, 2, 2, 3, 0, 4, 2};
  int val = 2;
  Solution sol;
  int res = sol.removeElement(nums, val);
  for (int i : nums) {
    cout << i << " ";
  }
  cout
      << endl
      << res;
  return 0;
}