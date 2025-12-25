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
class TreePrinter {
  public:
  /**
   * @param root The root of the tree
   * @param compact If true, uses 1 row per level. If false, uses 2 rows (connectors on separate lines).
   */
  static void print(TreeNode *root, bool compact = false, int max_depth = 15) {
    if (!root)
      return;

    // Allocate buffer: compact needs max_depth rows, normal needs max_depth * 2
    int rows = compact ? max_depth : max_depth * 2;
    vector<string> buffer(rows, string(200, ' '));

    _print_t(root, false, 0, 0, buffer, compact);

    for (const auto &row : buffer) {
      string trimmed = row;
      size_t end = trimmed.find_last_not_of(' ');
      if (end != string::npos) {
        cout << trimmed.substr(0, end + 1) << endl;
      } else if (!compact) {
        // In non-compact mode, we might want to skip totally empty connector rows
        continue;
      }
    }
  }

  private:
  static int _print_t(TreeNode *root, bool is_left, int offset, int depth, vector<string> &s, bool compact) {
    if (!root)
      return 0;

    int width = 5;
    char b[10];
    sprintf(b, "(%03d)", root->val);

    int left = _print_t(root->left, true, offset, depth + 1, s, compact);
    int right = _print_t(root->right, false, offset + left + width, depth + 1, s, compact);

    // Calculate row index based on mode
    int row = compact ? depth : 2 * depth;

    // Place node value
    for (int i = 0; i < width; i++)
      s[row][offset + left + i] = b[i];

    if (depth > 0) {
      // Determine connector row and characters
      int c_row = compact ? depth - 1 : 2 * depth - 1;
      char corner = compact ? '.' : '+';

      if (is_left) {
        for (int i = 0; i < width + right; i++)
          s[c_row][offset + left + width / 2 + i] = '-';

        s[c_row][offset + left + width / 2] = corner;
        if (!compact)
          s[c_row][offset + left + width + right + width / 2] = corner;
      } else {
        for (int i = 0; i < left + width; i++)
          s[c_row][offset - width / 2 + i] = '-';

        s[c_row][offset + left + width / 2] = corner;
        if (!compact)
          s[c_row][offset - width / 2 - 1] = corner;
      }
    }

    return left + width + right;
  }
};

int main() {
  vector<int> treeData = {1, 2, 3, -1, 4, 5, 6, 8, 9};
  TreeNode *root = buildTree(treeData);

  TreePrinter::print(root, false);
  cout << "\n\n\n";

  return 0;
}