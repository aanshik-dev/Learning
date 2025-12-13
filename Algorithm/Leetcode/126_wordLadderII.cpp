#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
    vector<vector<string>> res;
    unordered_set<string> ls;
    for (string w : wordList) {
      ls.insert(w);
    }
    if (!ls.count(endWord)) {
      return res;
    }
  }
};

class Solution {

  public:
  int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
    unordered_set<string> ls;
    for (string w : wordList) {
      ls.insert(w);
    }
    if (!ls.count(endWord)) {
      return 0;
    }
    queue<pair<string, int>> que;
    que.emplace(beginWord, 1);
    while (!que.empty()) {
      pair<string, int> p = que.front();
      que.pop();
      string word = p.first;
      for (int i = 0; i < p.first.length(); i++) {
        string temp = word;
        for (int j = 0; j < 26; j++) {
          temp[i] = 'a' + j;
          if (ls.count(temp)) {
            ls.erase(temp);
            if (temp == endWord) {
              return p.second + 1;
            }
            que.emplace(temp, p.second + 1);
          }
        }
      }
    }
    return 0;
  }
};

int main() {
  string begin = "hit", end = "cog";
  vector<string> wordList = {"hot", "dot", "lot", "log", "dog", "cog", "cot"};
  Solution sol;
  int res = sol.ladderLength(begin, end, wordList);
  cout << res << endl;
  return 0;
}