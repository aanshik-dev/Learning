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
TreeNode *buildTree(vector<int> tree) {

  if (tree.size() == 0)
    return nullptr;
  TreeNode *root = new TreeNode(tree[0]);
  queue<TreeNode *> q;
  q.push(root);
  TreeNode *cur;
  int i = 1;
  while (!q.empty() && i < tree.size()) {
    cur = q.front();
    q.pop();
    if (tree[i] != -1) {
      cur->left = new TreeNode(tree[i]);
      q.push(cur->left);
    }
    i++;
    if (tree[i] != -1) {
      cur->right = new TreeNode(tree[i]);
      q.push(cur->right);
    }
    i++;
  }
  return root;
}

class Solution {
  public:
  void postOrder(TreeNode *root, vector<int> &res) {
    if (!root)
      return;
    postOrder(root->left, res);
    postOrder(root->right, res);
    res.emplace_back(root->val);
  }

  public:
  vector<int> postorderTraversal(TreeNode *root) {
    vector<int> res;
    postOrder(root, res);
    return res;
  }
};

int main() {
  vector<int> tree = {1, 2, 3, -1, 4, 5, 6, 8, 9};
  TreeNode *root = buildTree(tree);
  Solution sol;
  vector<int> res = sol.postorderTraversal(root);
  for (int i : res) {
    cout << i << " ";
  }
  return 0;
}

//          1
//      2      3
//       4    5  6
//      8 9

// 5 6 8 9
// 1,2, 3, -1, 4, 5, 6, 8, 9, -1, -1, -1, -1 , -1,-1,-1,-1};