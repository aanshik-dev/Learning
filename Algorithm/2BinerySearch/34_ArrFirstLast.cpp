#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  vector<int> searchRange(vector<int> &nums, int target) {
    vector<int> res = {-1, -1};
    auto it1 = lower_bound(nums.begin(), nums.end(), target);
    auto it2 = upper_bound(nums.begin(), nums.end(), target);
    if (it1 == nums.end() || *it1 != target) {
      return res;
    }
    res[0] = it1 - nums.begin();
    res[1] = it2 - nums.begin() - 1;
    return res;
  }
};

int main() {
  vector<int> nums = {1, 1, 1, 5, 7, 7, 10};
  Solution sol;
  vector<int> res = sol.searchRange(nums, 10);
  cout << res[0] << res[1] << endl;
  return 0;
}