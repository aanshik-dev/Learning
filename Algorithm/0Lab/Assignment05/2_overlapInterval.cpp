#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool comparator(pair<int, int> p1, pair<int, int> p2) {
  return p1.second < p2.second;
}

int findBound(vector<int> &nums, int target) {
  auto bound = upper_bound(nums.begin(), nums.end(), target);
  if (bound == nums.begin())
    return *bound; // all numbers >= target
  --bound;
  return *bound;
}

vector<int> overlap(vector<pair<int, int>> &gaps, vector<int> &nums) {
  vector<int> X;
  int idx = -1, val = 0, n = nums.size();
  sort(gaps.begin(), gaps.end(), comparator);
  for (int i = 0; i < gaps.size(); i++) {
    if (idx >= 0 && X[idx] >= gaps[i].first) {
      continue;
    }
    val = findBound(nums, gaps[i].second);
    X.emplace_back(val);
    idx++;
  }
  return X;
}

int main() {
  vector<int> nums = {1, 2, 3, 4, 5, 6};
  vector<pair<int, int>> gaps = {{1, 6}, {2, 5}, {3, 4}};

  vector<int> res = overlap(gaps, nums);
  for (int i = 0; i < res.size(); i++) {
    cout << res[i] << " ";
  }
  return 0;
}