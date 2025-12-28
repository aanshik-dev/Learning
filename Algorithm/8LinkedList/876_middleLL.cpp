#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
  public:
  ListNode *middleNode(ListNode *head) {
    if (!head || !head->next) {
      return head;
    }
    ListNode *slow = head;
    ListNode *fast = head;
    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow;
  }
};

int main() {
  ListNode *root = new ListNode(2);
  ListNode *n1 = new ListNode(5);
  ListNode *n2 = new ListNode(-1);
  ListNode *n3 = new ListNode(6);
  ListNode *n4 = new ListNode(8);
  root->next = n1;
  n1->next = n2;
  n2->next = n3;
  // n3->next = n4;
  vector<int> nums = {};
  Solution sol;
  ListNode *mid = sol.middleNode(root);
  cout << mid->val << endl;
  return 0;
}