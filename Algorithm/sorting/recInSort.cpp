#include <bits/stdc++.h>
using namespace std;

void InSort(vector<int> &nums, int n) {
  
}

int main(){
    vector<int> nums = {2, 6, 3, 4, 1, 8, 9};
  int n = nums.size();
  InSort(nums, n);

  for (int i = 0; i < n; i++) {
    cout << nums[i] << " ";
  }
  return 0;
}