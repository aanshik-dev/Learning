#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
  public:
  int maxDepth(TreeNode *root) {
    if (root == nullptr) {
      return 0;
    }
    static int maxmm = 0;
    static int height = 0;
    
  }
};

int main() {

  TreeNode *m8 = new TreeNode(9);
  TreeNode *m7 = new TreeNode(8, m8, nullptr);
  TreeNode *m6 = new TreeNode(7);
  TreeNode *m5 = new TreeNode(6);
  TreeNode *m4 = new TreeNode(5, m5, m6);
  TreeNode *m3 = new TreeNode(4);
  TreeNode *m2 = new TreeNode(3, nullptr, m7);
  TreeNode *m1 = new TreeNode(2, m3, m4);
  TreeNode *rootM = new TreeNode(1, m1, m2);

  Solution sol;
  int res = sol.maxDepth(rootM);
  cout << res << endl;
  return 0;
}