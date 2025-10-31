#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int removeDuplicates(vector<int> &nums) {
    int uniq = nums[0];
    int pos = 0;
    for (int i = 1; i < nums.size(); i++) {
      if (nums[i] != uniq) {
        pos++;
        uniq = nums[i];
        nums[pos] = nums[i];
      }
    }
    return pos + 1;
  }
};

int main() {
  vector<int> nums = {1, 1, 2, 3, 4, 5};
  Solution sol;
  int res = sol.removeDuplicates(nums);
  cout << res << endl;
  return 0;
}