#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int minimumTotal(vector<vector<int>> &triangle) {
    int height = triangle.size();
    int base = triangle[height - 1].size();

    for (int i = 1; i < height; i++) {
      int x = height - i - 1;
      for (int j = 0; j < base - i; j++) {
        triangle[x][j] += min(triangle[x + 1][j], triangle[x + 1][j + 1]);
      }
    }

    return triangle[0][0];
  }
};

int main() {
  vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
  Solution sol;
  int res = sol.minimumTotal(triangle);
  cout << res << endl;
  return 0;
}

// 2
// 3 4
// 6 5 7
// 4 1 8 3

//  02
//  05  06
//  11  10  13
//  15  11  18  16

//  11
//  09  10
//  07  06  10
//  04  01  08  03