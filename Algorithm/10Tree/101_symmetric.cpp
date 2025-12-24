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
  void traverse(TreeNode *l, TreeNode *r, bool &res) {
    if (l == nullptr && r == nullptr) {
      return;
    }
    if (l == nullptr || r == nullptr) {
      res = false;
      return;
    }
    if (!res) {
      return;
    }
    traverse(l->left, r->right, res);
    if (l->val != r->val) {
      res = false;
      return;
    }
    traverse(l->right, r->left, res);
  }

  bool isSymmetric(TreeNode *root) {
    bool res = true;
    traverse(root->left, root->right, res);
    return res;
  }
};

int main() {
  TreeNode *n6 = new TreeNode(3);
  TreeNode *n5 = new TreeNode(4);
  TreeNode *n4 = new TreeNode(4);
  TreeNode *n3 = new TreeNode(3);
  TreeNode *n2 = new TreeNode(2, n5, n6);
  TreeNode *n1 = new TreeNode(2, n3, n4);
  TreeNode *root = new TreeNode(1, n1, n2);

  Solution sol;
  int res = sol.isSymmetric(root);
  cout << res << endl;
  return 0;
}