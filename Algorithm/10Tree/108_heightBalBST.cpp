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
  TreeNode *buildTree(int l, int r, vector<int> &nums) {
    if (l > r)
      return nullptr;
    int mid = l + (r - l) / 2;
    TreeNode *root = new TreeNode(nums[mid]);
    root->left = buildTree(l, mid - 1, nums);
    root->right = buildTree(mid + 1, r, nums);
    return root;
  }
  TreeNode *sortedArrayToBST(vector<int> &nums) {
    TreeNode *root = buildTree(0, nums.size() - 1, nums);
    return root;
  }
};

int main() {
  vector<int> nums = {-10, -3, 0, 5, 9};
  Solution sol;
  TreeNode *res = sol.sortedArrayToBST(nums);
  cout << res->val << res->left->val << res->right->val << res->left->right->val << res->right->right->val << endl;
  return 0;
}