#include <bits/stdc++.h>
using namespace std;

// class Solution {
//   public:
//   int lengthOfLongestSubstring(string s) {
//     vector<char> vect;
//     int max = 0, count = 0;
//     for (int i = 0; i < s.size(); i++) {
//       char c = s[i];
//       for (int j = 0; j < vect.size(); j++) {
//         if (c == vect[j]) {
//           max = max > count ? max : count;
//           vect.erase(vect.begin(), vect.begin() + j + 1);
//           count = vect.size();
//           break;
//         }
//       }
//       count++;
//       vect.push_back(c);
//     }
//     max = max > count ? max : count;
//     return max;
//   }
// };

class Solution {
  public:
  int lengthOfLongestSubstring(string s) {
    int left = 0, res = 0;
    set<char> st;

    for (int i = 0; i < s.size(); i++) {
      while (st.count(s[i])) {
        st.erase(s[left]);
        left++;
      };
      st.insert(s[i]);
      res = max(res, i - left + 1);
    }

    return res;
  }
};

int main() {
  Solution sol;
  int res = sol.lengthOfLongestSubstring("abcabcdf");
  cout << res << endl;
  return 0;
}