#include <iostream>
#include <vector>
using namespace std;

int balance(vector<int> &nums, int l, int r) {
  if (l == r)
    return 0;

  int mid = l + (r - l) / 2;
  int leftBal = balance(nums, l, mid);
  int rightBal = balance(nums, mid + 1, r);

  int zeros = 0, ones = 0;
  int maxL = 0, maxR = 0;

  for (int i = mid; i >= l; --i) {
    nums[i] == 0 ? ++zeros : ++ones;
    if (zeros == ones)
      maxL = zeros + ones;
  }

  zeros = ones = 0;
  for (int i = mid + 1; i <= r; ++i) {
    nums[i] == 0 ? ++zeros : ++ones;
    if (zeros == ones)
    maxR = zeros + ones;
  }
  
  int cross = maxL + maxR;
  int lrmax = max(leftBal, rightBal);
  return max(cross, lrmax);
}

int main() {
  int size;
  cout << "Enter the size of array : ";
  cin >> size;

  vector<int> nums(size);
  cout << "Enter the 0's and 1's : ";
  for (int &n : nums)
    cin >> n;

  cout << balance(nums, 0, size - 1);
  return 0;
}
