#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
  int lengthOfLongestSubstring(string s) {
    vector<char> vect;
    int max = 0, count = 0;
    for (int i = 0; i < s.size(); i++) {
      cout << s[i] << " ";
      char c = s[i];
      for (int j = 0; j < vect.size(); j++) {
        if (c == vect[j]) {
          max = max > count ? max : count;
          vect.erase(vect.begin(), vect.begin() + j + 1);
          count = vect.size();
          cout << "t" << count << "[";
          for (int k = 0; k < vect.size(); k++) {
            cout << vect[k];
          }
          cout << "] ";
          break;
        }
      }
      count++;
      vect.push_back(c);
      cout << count << " " << max << "|" << endl;
    }
    max = max > count ? max : count;
    return max;
  }
};

int main() {
  Solution sol;

  int res = sol.lengthOfLongestSubstring("dvdf");
  cout << res << endl;
  return 0;
}