#include <iostream>
#include <vector>
using namespace std;

class Solution {

  public:
  pair<int, int> findMajor(vector<int> &nums, int st, int end) {
    if (st < end) {
      int mid = st + (end - st) / 2;
      pair<int, int> maxL = findMajor(nums, st, mid);
      pair<int, int> maxR = findMajor(nums, mid + 1, end);
      if (maxL.first == maxR.first) {
        return {maxL.first, maxL.second + maxR.second};
      } else {
        int countL = 0, countR = 0;
        for (int i = st; i <= end; i++) {
          if (nums[i] == maxL.first) {
            countL++;
          }
          if (nums[i] == maxR.first) {
            countR++;
          }
        }
        return countL > countR ? pair<int, int>{maxL.first, countL} : pair<int, int>{maxR.first, countR};
      }
    }
    return {nums[st], 1};
  }

  public:
  void majorityElement(vector<int> &nums) {
    pair<int, int> res = findMajor(nums, 0, nums.size() - 1);
    if (res.second <= nums.size() / 2) {
      cout << "No Majority Element" << endl;
      return;
    }
    cout << res.first << " is majority element with count " << res.second << endl;
  }
};

int main() {
  Solution sol;

  vector<int> nums = {2,3,4,3,5,3,6,3,3};
  sol.majorityElement(nums);

  return 0;
}