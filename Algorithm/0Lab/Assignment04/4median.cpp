#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int kthSmall(vector<int> &nums, int k);

int partition(vector<int> &nums, int p) {
  int n = nums.size();
  int idx = 0;
  while (idx < n) {
    if (nums[idx] == p) {
      break;
    } else {
      idx++;
    }
  }
  swap(nums[idx], nums[n - 1]);
  int count = 0;
  for (int i = 0; i < n - 1; i++) {
    if (nums[i] < p) {
      swap(nums[i], nums[count]);
      count++;
    }
  }
  swap(nums[count], nums[n - 1]);
  return count;
}

int pivot(vector<int> &nums) {

  if (nums.size() == 1) {
    return nums[0];
  }

  int n = nums.size();
  for (int i = 0; i < n / 5; i++) {
    sort(nums.begin() + i * 5, nums.begin() + (i + 1) * 5);
  }
  vector<int> medVector;
  for (int i = 0; i < n / 5; i++) {
    medVector.push_back(nums[i * 5 + 2]);
  }

  int start = (n / 5) * 5;
  int size = n % 5;
  if (size > 0) {
    sort(nums.begin() + start, nums.end());
    medVector.push_back(nums[start + size / 2]);
  }

  int medOmed = kthSmall(medVector, medVector.size() / 2 + 1);
  return medOmed;
}

int kthSmall(vector<int> &nums, int k) {
  if (k > nums.size()) {
    cout << "Invalid position ";
    return -1;
  }
  int p = pivot(nums);
  int part = partition(nums, p);
  // cout << "[" << p << " " << part << "]" << endl;

  if (part + 1 == k) {
    return nums[part];
  } else if (part + 1 < k) {
    vector<int> right = vector<int>(nums.begin() + part + 1, nums.end());
    return kthSmall(right, k - part - 1);
  } else {
    vector<int> left = vector<int>(nums.begin(), nums.begin() + part);
    return kthSmall(left, k);
  }
}

int main() {
  vector<int> nums = {1, 5, 4, 8, 9, 7, 10, 6, 35, 14, 28, 3, 12, 19, 22, 28, 35, 20};
  int k = 5;
  int res = kthSmall(nums, k);
  cout
      << endl
      << k << "th smallest element is : " << res << endl;
  sort(nums.begin(), nums.end());
  cout << "Sorted array is : ";
  for (int i : nums)
    cout << i << " ";
  cout
      << endl
      << endl;

  return 0;
}