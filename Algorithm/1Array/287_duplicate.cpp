#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int findDuplicate(vector<int> &nums) {
    int size = nums.size() - 1;
    int sum = 0;
    for (int i = 0; i <= size; i++) {
      sum += nums[i];
    }
    int total = size * (size + 1) / 2;
    return sum - total;
  }
};

int main() {
  vector<int> nums = {1, 2, 3, 4, 6, 5, 7, 7};
  Solution sol;
  int res = sol.findDuplicate(nums);
  cout << res << endl;
  return 0;
}