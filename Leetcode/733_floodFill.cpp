#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color) {

    if (color == image[sr][sc])
      return image;
    int col = image[sr][sc];
    int n = image.size();
    int m = image[0].size();

    queue<pair<int, int>> q;
    q.emplace(sr, sc);
    image[sr][sc] = color;
    bool run = true;
    while (run) {
      int k = q.size();
      run = false;
      while (k > 0) {
        pair<int, int> s = q.front();
        int i = s.first, j = s.second;
        q.pop();
        if (i > 0 && image[i - 1][j] == col) {
          q.emplace(i - 1, j);
          image[i - 1][j] = color;
          run = true;
        }
        if (j > 0 && image[i][j - 1] == col) {
          q.emplace(i, j - 1);
          image[i][j - 1] = color;
          run = true;
        }
        if (i < n - 1 && image[i + 1][j] == col) {
          q.emplace(i + 1, j);
          image[i + 1][j] = color;
          run = true;
        }
        if (j < m - 1 && image[i][j + 1] == col) {
          q.emplace(i, j + 1);
          image[i][j + 1] = color;
          run = true;
        }
        k--;
      }
    }
    return image;
  }
};
int main() {
  Solution sol;
  vector<vector<int>> image = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
  int sr = 1, sc = 1, color = 2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2;
  vector<vector<int>> res = sol.floodFill(image, sr, sc, color);

  for (int i = 0; i < res.size(); i++) {
    for (int j = 0; j < res[0].size(); j++) {
      cout << res[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}
