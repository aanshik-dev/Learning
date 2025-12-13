#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int missingNumber(vector<int> &nums) {
    int n = nums.size();
    int sum = n * (n + 1) / 2;
    int num_sum = 0;
    for (int num : nums) {
      num_sum += num;
    }
    return sum - num_sum;
  }
};

int main() {

  vector<int> nums = {0, 1, 4, 3};
  Solution sol;
  int res = sol.missingNumber(nums);
  cout << res << endl;

  return 0;
}