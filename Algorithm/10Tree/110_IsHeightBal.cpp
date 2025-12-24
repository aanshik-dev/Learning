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
  int height(TreeNode *root) {
    if (!root) {
      return 0;
    }
    return max(height(root->left), height(root->right)) + 1;
  }

  bool isBalanced(TreeNode *root) {
    if (!root) {
      return true;
    }
    if (abs(height(root->left) - height(root->right)) > 1) {
      return false;
    }
    return isBalanced(root->left) && isBalanced(root->right);
  }
};

int main() {

  TreeNode *m5 = new TreeNode(5);
  TreeNode *m4 = new TreeNode(5, nullptr, m5);
  TreeNode *m3 = new TreeNode(4);
  TreeNode *m2 = new TreeNode(3, m3, m4);
  TreeNode *m1 = new TreeNode(2);
  TreeNode *rootM = new TreeNode(1, m1, m2);

  Solution sol;
  bool res = sol.isBalanced(rootM);
  cout << res << endl;
  return 0;
}