#include <iostream>
using namespace std;

class Solution {
  public:
  int getValue(char c) {
    if (c == 'I' || c == 'i')
      return 1;
    if (c == 'V' || c == 'v')
      return 5;
    if (c == 'X' || c == 'x')
      return 10;
    if (c == 'L' || c == 'l')
      return 50;
    if (c == 'C' || c == 'c')
      return 100;
    if (c == 'D' || c == 'd')
      return 500;
    if (c == 'M' || c == 'm')
      return 1000;
    return 0;
  }

  public:
  int romanToInt(string s) {
    int res = 0;
    for (int i = 0; i < s.length(); i++) {
      int value = getValue(s[i]);
      int valueNext = getValue(s[i + 1]);
      if (value < valueNext) {
        res -= value;
      } else {
        res += value;
      }
    }
    return res;
  }
};

int main() {
  Solution sol;
  int res = sol.romanToInt("mcmxciv");
  cout << res << endl;
  return 0;
}