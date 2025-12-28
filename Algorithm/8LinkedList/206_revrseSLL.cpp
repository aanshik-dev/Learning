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
  ListNode *reverseList(ListNode *head) {
    ListNode *pre = nullptr;
    ListNode *cur = head;
    ListNode *nxt = nullptr;
    while (cur) {
      nxt = cur->next;
      cur->next = pre;
      pre = cur;
      cur = nxt;
    }
    return pre;
  }

  // Recursive
  ListNode *reverseList(ListNode *head) {
    if (!head || !head->next) {
      return head;
    }
    ListNode *res = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return res;
  }
};

int main() {

  ListNode *n5 = new ListNode(6);
  ListNode *n4 = new ListNode(5, n5);
  ListNode *n3 = new ListNode(4, n4);
  ListNode *n2 = new ListNode(3, n3);
  ListNode *n1 = new ListNode(2, n2);
  ListNode *n0 = new ListNode(1, n1);

  Solution sol;
  ListNode *res = sol.reverseList(n0);
  while (res != nullptr) {
    cout << res->val << " ";
    res = res->next;
  }
  return 0;
}