#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode *prev;
  ListNode(int x) : val(x), next(NULL), prev(NULL) {}
};

ListNode *reverseDLL(ListNode *head) {
  if (!head || !head->next)
    return head;
  ListNode *current = head;
  ListNode *temp = nullptr;
  while (current != nullptr) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }
  return temp->prev;
}

int main() {
  ListNode *root = new ListNode(2);
  ListNode *n1 = new ListNode(5);
  ListNode *n2 = new ListNode(-1);
  ListNode *n3 = new ListNode(6);
  ListNode *n4 = new ListNode(8);
  root->next = n1;
  n1->prev = root, n1->next = n2;
  n2->prev = n1, n2->next = n3;
  n3->prev = n2, n3->next = n4;
  n4->prev = n3;
  ListNode *head = reverseDLL(root);
  cout << head->val << head->next->val << head->next->next->val << head->next->next->next->val << head->next->next->next->next->val << endl;
  return 0;
}