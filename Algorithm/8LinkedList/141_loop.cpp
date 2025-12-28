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
  bool hasCycle(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) {
        return true;
      }
    }
    return false;
  }
};

int main() {

  ListNode *n5 = new ListNode(6);
  ListNode *n4 = new ListNode(5, n5);
  ListNode *n3 = new ListNode(4, n4);
  ListNode *n2 = new ListNode(3, n3);
  ListNode *n1 = new ListNode(2, n2);
  ListNode *n0 = new ListNode(1, n1);
  n5->next = n3;
  Solution sol;
  bool res = sol.hasCycle(n0);
  cout << res << endl;
  return 0;
}