#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n, inp;
  vector<int> nums;
  cout << "Please enter the size of the array: ";
  cin >> n;

  cout << "Please enter the array: ";
  for (int i = 0; i < n; i++) {
    cin >> inp;
    nums.push_back(inp);
  }
  vector<int> count(n, 1);
  for (int i = 1; i < n; i++) {
    for (int j = i - 1; j >= 0; j--) {
      if (nums[j] < nums[i] && count[i] < count[j] + 1) {
        count[i] = count[j] + 1;
      }
    }
  }

  cout << "The Largest Increasing Subarray Size: " << count.back();
}