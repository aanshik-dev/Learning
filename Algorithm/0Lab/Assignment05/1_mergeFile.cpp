#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
  vector<int> nums = {1, 2, 3, 4, 5};
  priority_queue<int, vector<int>, greater<int>> pq(nums.begin(), nums.end());
  int n = nums.size();

  int total = n == 1 ? nums[0] : 0;

  for (int i = 1; i < n; i++) {
    int a = pq.top();
    pq.pop();
    int b = pq.top();
    pq.pop();
    total += a + b;
    pq.push(a + b);
  }

  cout << total << endl;

  return 0;
}