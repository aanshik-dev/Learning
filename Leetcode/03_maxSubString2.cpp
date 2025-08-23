#include <iostream>
#include <set>
using namespace std;

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

  int res = sol.lengthOfLongestSubstring("abcabcde");
  cout << res << endl;
  return 0;
}