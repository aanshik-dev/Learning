#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<vector<int>> adList = {{2, 3}, {4}, {2, 5}, {}, {1, 4}};

  vector<vector<int>> mat = vector<vector<int>>(adList.size(), vector<int>(adList.size(), 0));

  for (int i = 0; i < adList.size(); i++) {
    for (int j = 0; j < adList[i].size(); j++) {
      mat[i][adList[i][j] - 1] = 1;
    }
  }

  for (int i = 0; i < mat.size(); i++) {
    for (int j = 0; j < mat[i].size(); j++) {
      cout << mat[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}