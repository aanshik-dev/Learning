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
  void inorder(TreeNode *root, vector<int> &vect) {
    if (root == nullptr)
      return;
    inorder(root->left, vect);
    vect.emplace_back(root->val);
    inorder(root->right, vect);
  }

  vector<int> inorderTraversal(TreeNode *root) {
    vector<int> res;
    inorder(root, res);
    return res;
  }
};

int main() {
  TreeNode *n8 = new TreeNode(9);
  TreeNode *n7 = new TreeNode(8, n8, nullptr);
  TreeNode *n6 = new TreeNode(7);
  TreeNode *n5 = new TreeNode(6);
  TreeNode *n4 = new TreeNode(5, n5, n6);
  TreeNode *n3 = new TreeNode(4);
  TreeNode *n2 = new TreeNode(3, nullptr, n7);
  TreeNode *n1 = new TreeNode(2, n3, n4);
  TreeNode *root = new TreeNode(1, n1, n2);

  Solution sol;
  vector<int> res = sol.inorderTraversal(root);

  cout << "Inorder Traversal: ";
  for (int x : res) {
    cout << x << " ";
  }
  cout << endl;

  return 0;
}
