#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  vector<int> findUnion(vector<int> &nums1, vector<int> &nums2) {
    int i = 0, j = 0;
    vector<int> res;
    while (i < nums1.size() && j < nums2.size()) {
      if (nums1[i] < nums2[j]) {
        res.push_back(nums1[i]);
        i++;
      } else if (nums1[i] > nums2[j]) {
        res.push_back(nums2[j]);
        j++;
      } else {
        res.push_back(nums1[i]);
        i++;
        j++;
      }
    }
    while (i < nums1.size()) {
      res.push_back(nums1[i]);
      i++;
    }
    while (j < nums2.size()) {
      res.push_back(nums2[j]);
      j++;
    }
    return res;
  }
};

int main() {

  vector<int> nums1 = {2, 4, 5, 6, 8, 9};
  vector<int> nums2 = {1, 2, 3, 5, 8};
  Solution sol;
  vector<int> nums = sol.findUnion(nums1, nums2);

  for (int i = 0; i < nums.size(); i++) {
    cout << nums[i] << " ";
  }

  return 0;
}