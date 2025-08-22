#include <iostream>
#include <vector>
using namespace std;

int frogJump(int n, vector<int> nums) {
  vector<int> vect(n, 0);
  vect[1] = nums[1] - nums[0];
  for (int i = 2; i < n; i++) {
    int enrG1 = vect[i - 1] + abs(nums[i] - nums[i - 1]);
    int enrG2 = vect[i - 2] + abs(nums[i] - nums[i - 2]);
    cout << enrG1 << " " << enrG2 << endl;
    if (enrG1 < enrG2) {
      vect[i] = enrG1;
    } else {
      vect[i] = enrG2;
    }
  }
  return vect.back();
}

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

  int enrG = frogJump(n, nums);

  cout << "The Minimum Energy Required: " << enrG;
}