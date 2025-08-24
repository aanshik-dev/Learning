#include <iostream>
#include <stack>
using namespace std;

class Solution {
  public:
  bool isValid(string s) {
    stack<char> st;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
        st.push(s[i]);
      } else if (s[i] == ')' && !st.empty() && st.top() == '(') {
        st.pop();
      } else if (s[i] == '}' && !st.empty() && st.top() == '{') {
        st.pop();
      } else if (s[i] == ']' && !st.empty() && st.top() == '[') {
        st.pop();
      } else {
        return false;
      }
    }
    return st.empty();
  }
};

int main() {
  Solution sol;
  bool res = sol.isValid("[)()]");
  cout << res << endl;
  return 0;
}