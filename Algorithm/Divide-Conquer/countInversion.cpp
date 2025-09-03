// P9: Counting Inversion I/P: Given an array A of distinct integers.
// O/P: The number of inversions of A is the number of pairs (i,j) of array A with i<j and A[i] > A[j].

#include <iostream>
#include <vector>
using namespace std;

int countInv(vector<int> &nums, int l, int r) {

  if (l == r) {
    return 0;
  }
  int mid = l + (r - l) / 2;
  int left = countInv(nums, l, mid);
  int right = countInv(nums, mid + 1, r);

  vector<int> merged;
  int i = l, j = mid + 1;
  int inv = 0;

  while (i <= mid && j <= r) {
    if (nums[i] <= nums[j]) {
      merged.push_back(nums[i++]);
    } else {
      inv += (mid - i + 1);
      merged.push_back(nums[j++]);
    }
  }

  while (i <= mid)
    merged.push_back(nums[i++]);
  while (j <= r)
    merged.push_back(nums[j++]);

  for (int k = 0; k < merged.size(); k++) {
    nums[l + k] = merged[k];
  }

  return left + right + inv;
}

int main() {
  vector<int> nums = {1, 3, 5, 2, 4, 6};
  int res = countInv(nums, 0, nums.size() - 1);
  cout << res << endl;
  return 0;
}