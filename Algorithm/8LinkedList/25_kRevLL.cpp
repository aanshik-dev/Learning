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
  ListNode *reverseKGroup(ListNode *head, int k) {
    ListNode *tail = nullptr;
    ListNode *res = nullptr;
    while (head != nullptr) {
      ListNode *prev = nullptr;
      ListNode *curr = head;
      ListNode *nxt = nullptr;
      int t = 0;
      for (int i = 0; i < k; i++) {
        if (curr == nullptr) {
          break;
        }
        t = i + 1;
        curr = curr->next;
      }
      curr = head;
      if (t != k) {
        if (tail != nullptr) {
          tail->next = curr;
        }
        break;
      }
      for (int i = 0; i < k; i++) {
        nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
      }
      if (!res) {
        res = prev;
      }
      if (tail != nullptr) {
        tail->next = prev;
      }
      tail = head;
      head = curr;
    }
    return res;
  }
};
// 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8
// 3 -> 2 -> 1 n  6 -> 5 -> 4
int main() {

  ListNode *n5 = new ListNode(6);
  ListNode *n4 = new ListNode(5, n5);
  ListNode *n3 = new ListNode(4, n4);
  ListNode *n2 = new ListNode(3, n3);
  ListNode *n1 = new ListNode(2, n2);
  ListNode *n0 = new ListNode(1, n1);
  Solution sol;
  ListNode *res = sol.reverseKGroup(n0, 3);
  while (res != nullptr) {
    cout << res->val << " ";
    res = res->next;
  }
  return 0;
}