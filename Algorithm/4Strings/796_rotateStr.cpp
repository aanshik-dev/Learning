#include <bits/stdc++.h>
using namespace std;

// S + S must contain the goal
class Solution {
  public:
  bool rotateString(string s, string goal) {
    if (s.length() != goal.length()) {
      return false;
    }
    return (s.append(s)).find(goal) != string::npos;
  }
};

int main() {
  string s = "bbbacddceeb", goal = "ceebbbbacdd";
  Solution sol;
  bool res = sol.rotateString(s, goal);
  cout << res << endl;
  return 0;
}