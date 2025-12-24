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

// class Solution {
//   public:
//   bool isSameTree(TreeNode *p, TreeNode *q) {
//     if (p == nullptr && q == nullptr)
//       return true;
//     if (p == nullptr || q == nullptr)
//       return false;
//     if (p->val != q->val)
//       return false;

//     return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
//   }
// };

class Solution {
  public:
  void inorder(TreeNode *rootM, TreeNode *rootN, bool &res) {
    if (rootM == nullptr && rootN == nullptr) {
      return;
    }
    if (rootM == nullptr || rootN == nullptr) {
      res = false;
      return;
    }
    if (!res) {
      return;
    }
    inorder(rootM->left, rootN->left, res);
    if (rootM->val != rootN->val) {
      res = false;
      return;
    }
    inorder(rootM->right, rootN->right, res);
  }

  bool isSameTree(TreeNode *p, TreeNode *q) {
    bool res = true;
    inorder(p, q, res);
    return res;
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

  TreeNode *n8 = new TreeNode(9);
  TreeNode *n7 = new TreeNode(8, n8, nullptr);
  TreeNode *n6 = new TreeNode(7);
  TreeNode *n5 = new TreeNode(6);
  TreeNode *n4 = new TreeNode(5, n5, n6);
  TreeNode *n3 = new TreeNode(4);
  TreeNode *n2 = new TreeNode(3, nullptr, n7);
  TreeNode *n1 = new TreeNode(2, n3, n4);
  TreeNode *rootN = new TreeNode(1, n1, n2);

  Solution sol;
  bool res = sol.isSameTree(rootM, rootN);
  cout << res << endl;
  return 0;
}