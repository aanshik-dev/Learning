#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    m--;
    n--;
    int idx = nums1.size() - 1;
    while (m >= 0 || n >= 0) {
      int x = INT_MIN, y = INT_MIN;
      if (m >= 0) {
        x = nums1[m];
      }
      if (n >= 0) {
        y = nums2[n];
      }
      if (x > y) {
        nums1[idx--] = x;
        m--;
      } else {
        nums1[idx--] = y;
        n--;
      }
    }
  }
};

int main() {
  vector<int> nums1 = {1, 3, 3, 6, 7, 9, 0, 0, 0, 0, 0, 0, 0};
  vector<int> nums2 = {2, 3, 5, 6, 6, 9, 11};
  Solution sol;
  sol.merge(nums1, 6, nums2, 7);
  for (int i : nums1) {
    cout << i << " ";
  }
  return 0;
}