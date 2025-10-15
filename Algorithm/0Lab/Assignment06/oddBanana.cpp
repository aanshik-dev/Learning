// LOGIC : maintain odd and even dp where ith element stores the max number of odd/even bananas till i.
#include <bits/stdc++.h>
using namespace std;

int main() {

  vector<vector<int>> nums = {{2, 5, 1, 5, 2}, {1, 1, 3, 4, 5}, {3, 6, 4, 2, 1}, {1, 2, 1, 2, 1}};

  // 2 5 1 5 2   [2,0] [00,7] [08,00] [00,13] [00,15]
  // 1 1 3 4 5   [0,3] [08,0] [00,11] [00,17] [22,00]
  // 3 6 4 2 1   [6,0] [14,0] [18,15] [20,19] [20,23]
  // 1 2 1 2 1   [0,7] [16,9] [16,19] [22,21] [24,23]

  int row = nums.size();
  int col = nums[0].size();

  vector<vector<int>> odd(row, vector<int>(col, 0));
  vector<vector<int>> even(row, vector<int>(col, 0));

  odd[0][0] = nums[0][0] % 2 == 1 ? nums[0][0] : 0;
  even[0][0] = nums[0][0] % 2 == 0 ? nums[0][0] : 0;

  for (int i = 1; i < col; i++) {
    if (nums[0][i] % 2 == 0) {
      odd[0][i] = odd[0][i - 1] == 0 ? 0 : nums[0][i] + odd[0][i - 1];
      even[0][i] = even[0][i - 1] == 0 ? 0 : nums[0][i] + even[0][i - 1];
    } else {
      odd[0][i] = even[0][i - 1] == 0 ? 0 : nums[0][i] + even[0][i - 1];
      even[0][i] = odd[0][i - 1] == 0 ? 0 : nums[0][i] + odd[0][i - 1];
    }
  }

  for (int i = 1; i < row; i++) {
    if (nums[i][0] % 2 == 0) {
      odd[i][0] = odd[i - 1][0] == 0 ? 0 : nums[i][0] + odd[i - 1][0];
      even[i][0] = even[i - 1][0] == 0 ? 0 : nums[i][0] + even[i - 1][0];
    } else {
      odd[i][0] = even[i - 1][0] == 0 ? 0 : nums[i][0] + even[i - 1][0];
      even[i][0] = odd[i - 1][0] == 0 ? 0 : nums[i][0] + odd[i - 1][0];
    }
  }

  for (int i = 1; i < row; i++) {
    for (int j = 1; j < col; j++) {
      int oddmax = max(odd[i - 1][j], odd[i][j - 1]);
      int evenmax = max(even[i - 1][j], even[i][j - 1]);
      if (nums[i][j] % 2 == 0) {
        odd[i][j] = oddmax == 0 ? 0 : nums[i][j] + oddmax;
        even[i][j] = evenmax == 0 ? 0 : nums[i][j] + evenmax;
      } else {
        odd[i][j] = evenmax == 0 ? 0 : nums[i][j] + evenmax;
        even[i][j] = oddmax == 0 ? 0 : nums[i][j] + oddmax;
      }
    }
  }

  cout << "The maximum number of odd bananas are: " << odd[row - 1][col - 1] << endl;
  cout << "The maximum number of even bananas are: " << even[row - 1][col - 1] << endl;
  return 0;
}