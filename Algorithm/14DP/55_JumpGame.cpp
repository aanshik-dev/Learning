#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
  int canJump(vector<int> &nums) {
    bool jump = true;
    int leap = 1;
    for (int i = nums.size() - 2; i >= 0; i--) {
      jump = false;
      if (nums[i] >= max(1, leap)) {
        leap = 1;
        jump = true;
      } else {
        leap++;
        jump = false;
      }
    }
    return jump;
  }
};

int main() {
  Solution sol;
  vector<int> nums = {2, 0, 3, 5};
  bool canJump = sol.canJump(nums);
  cout << canJump << endl;

  return 0;
}