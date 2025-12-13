#include <bits/stdc++.h>
using namespace std;

void bubbleSort(vector<int> &nums, int n) {
  if (n <= 1) {
    return;
  }
  for (int i = 1; i < n; i++) {
    if (nums[i] < nums[i - 1]) {
      swap(nums[i], nums[i - 1]);
    }
  }
  bubbleSort(nums, n - 1);
  return;
}

int main() {
  vector<int> nums = {2, 6, 3, 4, 1, 8, 9};
  int n = nums.size();
  bubbleSort(nums, n);

  for (int i = 0; i < n; i++) {
    cout << nums[i] << " ";
  }
  return 0;
}