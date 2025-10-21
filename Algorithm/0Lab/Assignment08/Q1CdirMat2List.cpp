#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<vector<int>> matrix = {{0, 1, 1, 0, 0}, {0, 0, 0, 1, 0}, {0, 1, 0, 0, 1}, {0, 0, 0, 0, 0}, {1, 0, 0, 1, 0}};

  map<char, vector<char>> m;
  for (int i = 0; i < matrix.size(); i++) {
    char c = 'A' + i;
    m.emplace(c, vector<char>());
    for (int j = 0; j < matrix[i].size(); j++) {
      if (matrix[i][j] == 1) {
        m[c].push_back('A' + j);
      }
    }
  }

  for (auto it = m.begin(); it != m.end(); it++) {
    cout << it->first << " : ";
    for (int i = 0; i < it->second.size(); i++) {
      cout << it->second[i] << " ";
    }
    cout << endl;
  }

  return 0;
}