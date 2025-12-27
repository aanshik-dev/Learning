#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
  public:
  void deleteNode(ListNode *node) {
    node->val = node->next->val;
    node->next = node->next->next;
  }
};

// <- 1 -> <- 2 -><- 3 -><- 4 ->
//             <- 2 -> <- 1 ->
int main() {
  ListNode *root = new ListNode(2);
  ListNode *n1 = new ListNode(5);
  ListNode *n2 = new ListNode(-1);
  ListNode *n3 = new ListNode(6);
  ListNode *n4 = new ListNode(8);
  root->next = n1;
  n1->next = n2;
  n2->next = n3;
  n3->next = n4;

  Solution sol;
  sol.deleteNode(n3);
  cout << root->val << root->next->val << root->next->next->val << root->next->next->next->val << endl;
  return 0;
}