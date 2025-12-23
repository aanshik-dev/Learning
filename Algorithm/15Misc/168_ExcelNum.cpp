#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  string convertToTitle(int columnNumber) {
    string res = "";

    while (columnNumber > 0) {
      columnNumber--;
      res = char((columnNumber % 26) + 'A') + res;
      columnNumber /= 26;
    }
    return res;
  }
};

int main() {

  int columnNumber = 18250;
  Solution sol;
  string res = sol.convertToTitle(columnNumber);
  cout << res << endl;
  return 0;
}