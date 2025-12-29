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
  ListNode *rotateRight(ListNode *head, int k) {
    if (!head || !head->next) {
      return head;
    }
    int len = 1;
    ListNode *curr = head;
    while (curr->next != nullptr) {
      len++;
      curr = curr->next;
    }
    k %= len;
    curr->next = head;
    curr = head;
    for (int i = 0; i < len - k - 1; i++) {
      curr = curr->next;
    }
    head = curr->next;
    curr->next = nullptr;
    return head;
  }
};

// 1 -> 2 -> 3 -> 4 -> 5 -> 6

int main() {

  ListNode *n5 = new ListNode(6);
  ListNode *n4 = new ListNode(5, n5);
  ListNode *n3 = new ListNode(4, n4);
  ListNode *n2 = new ListNode(3, n3);
  ListNode *n1 = new ListNode(2, n2);
  ListNode *n0 = new ListNode(1, n1);

  Solution sol;
  ListNode *res = sol.rotateRight(n0, 7);
  while (res != nullptr) {
    cout << res->val << " ";
    res = res->next;
  }
  return 0;
}