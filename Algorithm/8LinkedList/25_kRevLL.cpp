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
    while (head != nullptr) {
      ListNode *prev = nullptr;
      ListNode *curr = head;
      ListNode *nxt = nullptr;
      for (int i = 0; i < k && head != nullptr; i++) {
        nxt = head->next;
        head->next = prev;
        prev = head;
        head = nxt;
      }
    }
  }
};
// <- 1 -> <- 2 -> <- 3 -> <- 4 -> <- 5 ->
//  2 -> 1 -> 
int main() {

  ListNode *n5 = new ListNode(6);
  ListNode *n4 = new ListNode(5, n5);
  ListNode *n3 = new ListNode(4, n4);
  ListNode *n2 = new ListNode(3, n3);
  ListNode *n1 = new ListNode(2, n2);
  ListNode *n0 = new ListNode(1, n1);
  Solution sol;
  ListNode *res = sol.reverseKGroup(n0, 2);
  while (res != nullptr) {
    cout << res->val << " ";
    res = res->next;
  }
  return 0;
}