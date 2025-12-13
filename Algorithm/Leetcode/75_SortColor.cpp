#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  void sortColors(vector<int> &nums) {
    int zero = 0, one = 0, two = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] == 0) {
        zero++;
      } else if (nums[i] == 1) {
        one++;
      } else {
        two++;
      }
    }
    for (int i = 0; i < nums.size(); i++) {
      if (zero > 0) {
        nums[i] = 0;
        zero--;
      } else if (one > 0) {
        nums[i] = 1;
        one--;
      } else {
        nums[i] = 2;
        two--;
      }
    }
  }
};

int main() {
  vector<int> nums = {10, 1};
  Solution sol;
  sol.sortColors(nums);

  for (int i = 0; i < nums.size(); i++)
    cout << nums[i] << " ";
  return 0;
}