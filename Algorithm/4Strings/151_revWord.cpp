#include <bits/stdc++.h>
using namespace std;

// class Solution {
//   public:
//   string reverseWords(string s) {
//     string res;
//     int st = 0, end = 0;
//     int len = s.size();
//     for (int i = 0; i < len; i++) {
//       while (i < len && s[i] == ' ') {
//         i++;
//       }
//       st = i;
//       cout << "s" << st << " ";
//       while (i < len && s[i] != ' ') {
//         i++;
//       }
//       end = i--;
//       cout << "e" << end << endl;
//       if (st < len){
//         res = s.substr(st, end - st) + " " + res;
//       }
//     }
//     return res.substr(0, res.size() - 1);
//   }
// };

// class Solution {
//   public:
//   string reverseWords(string s) {
//     reverse(s.begin(), s.end());
//     int st = 0, end = 0;
//     for (int i = 0; i < s.size(); i++) {
//       while (i < s.size() && s[i] == ' ') {
//         s.erase(i, 1);
//       }
//       st = i;
//       while (i < s.size() && s[i] != ' ') {
//         i++;
//       }
//       end = i;
//       reverse(s.begin() + st, s.begin() + end);
//     }
//     if(s[s.size()-1] == ' '){
//       s.erase(s.size()-1);
//     }
//     return s;
//   }
// };

class Solution {
  public:
  string reverseWords(string s) {
    reverse(s.begin(), s.end());
    int n = s.size();
    int left = 0;
    int right = 0;
    for (int i = 0; i < n; i++) {
      while (i < n && s[i] == ' ')
        i++;
      if (i == n)
        break;
      while (i < n && s[i] != ' ') {
        s[right++] = s[i++];
      }
      reverse(s.begin() + left, s.begin() + right);
      s[right++] = ' ';
      left = right;
    }
    s.resize(right - 1);
    return s;
  }
};

int main() {
  string s = "   Hi  boss hiii  ";
  Solution sol;
  string res = sol.reverseWords(s);
  cout << res << endl;

  return 0;
}