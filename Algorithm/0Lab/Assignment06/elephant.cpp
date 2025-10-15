// Method:  make a dp, and initiate the first row and first column with the succesive sum. now starting from 1,1 take max of top and left and add current value

#include <bits/stdc++.h>
using namespace std;

int main() {

  vector<vector<int>> nums = {{2, 5, 1, 3, 2}, {1, 2, 3, 4, 5}, {3, 6, 4, 2, 1}, {1, 2, 1, 2, 1}};

  int row = nums.size();
  int col = nums[0].size();

  for (int i = 1; i < col; i++) {
    nums[0][i] = nums[0][i - 1] + nums[0][i];
  }

  for (int i = 1; i < row; i++) {
    nums[i][0] = nums[i - 1][0] + nums[i][0];
  }

  for (int i = 1; i < row; i++) {
    for (int j = 1; j < col; j++) {
      nums[i][j] = max(nums[i - 1][j], nums[i][j - 1]) + nums[i][j];
    }
  }
  cout << "The maximum number of bananas are: " << nums[row - 1][col - 1] << endl;

  return 0;
}