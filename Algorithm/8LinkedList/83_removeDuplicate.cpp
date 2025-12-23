#include <bits/stdc++.h>
using namespace std;

//  Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
  public:
  ListNode *deleteDuplicates(ListNode *head) {
    ListNode *h = head;
    while (h != nullptr && h->next != nullptr) {
      if (h->next->val == h->val) {
        ListNode *temp = h->next;
        h->next = h->next->next;
        delete temp;
      } else {
        h = h->next;
      }
    }
    return head;
  }
};

int main() {
  ListNode *n7 = new ListNode(5);
  ListNode *n6 = new ListNode(5, n7);
  ListNode *n5 = new ListNode(3, n6);
  ListNode *n4 = new ListNode(2, n5);
  ListNode *n3 = new ListNode(1, n4);
  ListNode *n2 = new ListNode(1, n3);
  ListNode *n1 = new ListNode(0, n2);
  ListNode *head = new ListNode(0, n1);
  Solution sol;
  ListNode *res = sol.deleteDuplicates(head);
  while (res != nullptr) {
    cout << res->val << " ";
    res = res->next;
  }
  return 0;
}
