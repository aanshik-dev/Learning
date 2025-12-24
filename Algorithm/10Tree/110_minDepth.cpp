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
  void bfs(int node, vector<vector<int>> &adj, vector<int> &vis) {
    queue<int> q;
    q.push(node);
    vis[node] = 1;
    while (!q.empty()) {
      int curr = q.front();
      q.pop();
      cout << curr << " ";
      for (auto i : adj[curr]) {
        if (!vis[i]) {
          q.push(i);
          vis[i] = 1;
        }
      }
    }
  }
  int minDepth(TreeNode *root) {
    queue<TreeNode> q;
    while(!q.empty()){
      
    }
    // minDepth(root->left) + 1, minDepth(root->right) + 1);
  }
};

int main() {

  TreeNode *n5 = new TreeNode(6);
  TreeNode *n4 = new TreeNode(5, nullptr, n5);
  TreeNode *n3 = new TreeNode(4);
  TreeNode *n2 = new TreeNode(3, n3, n4);
  TreeNode *n1 = new TreeNode(2);
  TreeNode *root = new TreeNode(1, n1, n2);

  Solution sol;
  bool res = sol.minDepth(root);
  cout << res << endl;
  return 0;
}