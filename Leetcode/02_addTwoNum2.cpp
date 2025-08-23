#include <iostream>
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
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    int carry = 0;
    ListNode *cur1 = l1;
    ListNode *cur2 = l2;

    ListNode *head = nullptr;
    ListNode *cur = nullptr;

    while (cur1 || cur2) {
      int val1 = cur1 ? cur1->val : 0;
      int val2 = cur2 ? cur2->val : 0;
      int sum = val1 + val2 + carry;
      int val = sum % 10;
      carry = sum / 10;

      if (!head) {
        head = new ListNode(val);
        cur = head;
      } else {
        cur->next = new ListNode(val);
        cur = cur->next;
      }

      cur1 = cur1 ? cur1->next : nullptr;
      cur2 = cur2 ? cur2->next : nullptr;
    }
    if (carry) {
      cur->next = new ListNode(carry);
    }
    return head;
  }
};

int main() {
  Solution sol;
  ListNode *Nodea5 = new ListNode(9);
  ListNode *Nodea4 = new ListNode(9, Nodea5);
  ListNode *Nodea3 = new ListNode(9, Nodea4);
  ListNode *Nodea2 = new ListNode(9, Nodea3);
  ListNode *Nodea1 = new ListNode(9, Nodea2);

  ListNode *Nodeb6 = new ListNode(9);
  ListNode *Nodeb5 = new ListNode(9, Nodeb6);
  ListNode *Nodeb4 = new ListNode(9, Nodeb5);
  ListNode *Nodeb3 = new ListNode(9, Nodeb4);
  ListNode *Nodeb2 = new ListNode(9, Nodeb3);
  ListNode *Nodeb1 = new ListNode(9, Nodeb2);

  ListNode *result = sol.addTwoNumbers(Nodea1, Nodeb1);

  while (result) {
    cout << result->val << endl;
    result = result->next;
  }

  return 0;
}