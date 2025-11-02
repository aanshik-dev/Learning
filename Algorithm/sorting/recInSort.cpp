#include <bits/stdc++.h>
using namespace std;

void InSort(vector<int> &nums, int n) {
  if (n <= 0) {
    return;
  }
  InSort(nums, n - 1);
  int curr = nums[n];
  int i = n - 1;
  while (nums[i] > curr && i >= 0) {
    nums[i + 1] = nums[i];
    i--;
  }
  nums[i + 1] = curr;
}

int main() {
  vector<int> nums = {18, 6, 3, 4, 1, 8, 9};
  int n = nums.size();
  InSort(nums, n - 1);

  for (int i = 0; i < n; i++) {
    cout << nums[i] << " ";
  }
  return 0;
}