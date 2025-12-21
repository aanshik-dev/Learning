#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  void cover(vector<vector<char>> &board, int i, int j) {
    board[i][j] = 'A';
    if (i > 0 && board[i - 1][j] == 'O') {
      cover(board, i - 1, j);
    }
    if (i < board.size() - 1 && board[i + 1][j] == 'O') {
      cover(board, i + 1, j);
    }
    if (j > 0 && board[i][j - 1] == 'O') {
      cover(board, i, j - 1);
    }
    if (j < board[0].size() - 1 && board[i][j + 1] == 'O') {
      cover(board, i, j + 1);
    }
  }

  public:
  void solve(vector<vector<char>> &board) {
    int n = board.size();
    int m = board[0].size();

    for (int i = 0; i < n; i++) {
      if (board[i][0] == 'O') {
        cover(board, i, 0);
      }
      if (board[i][m - 1] == 'O') {
        cover(board, i, m - 1);
      }
    }
    for (int j = 0; j < m; j++) {
      if (board[0][j] == 'O') {
        cover(board, 0, j);
      }
      if (board[n - 1][j] == 'O') {
        cover(board, n - 1, j);
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (board[i][j] == 'O') {
          board[i][j] = 'X';
        }
        if (board[i][j] == 'A') {
          board[i][j] = 'O';
        }
      }
    }
  }
};

int main() {
  vector<vector<char>> area = {
      {'X'}};

  Solution sol;
  sol.solve(area);
  for (int i = 0; i < area.size(); i++) {
    for (int j = 0; j < area[0].size(); j++) {
      cout << area[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
