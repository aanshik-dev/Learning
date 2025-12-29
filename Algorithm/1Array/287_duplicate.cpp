#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int findDuplicate(vector<int> &nums) {
    int size = nums.size();
    unordered_map<int, int> mp;
    for (int i = 0; i < size; i++) {
      mp[nums[i]]++;
      if (mp[nums[i]] > 1)
        return nums[i];
    }
    return -1;
  }
};

int main() {
  vector<int> nums = {1, 2, 3, 4, 6, 5, 7, 7};
  Solution sol;
  int res = sol.findDuplicate(nums);
  cout << res << endl;
  return 0;
}