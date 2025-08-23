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
  int makeNum(ListNode *ll) {
    // cout<< ll->val << endl;
    if (ll->next == nullptr) {
      return ll->val;
    }
    int sum = makeNum(ll->next);
    sum = sum * 10 + ll->val;
    return sum;
  }

  public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    int num1 = makeNum(l1);
    int num2 = makeNum(l2);
    int sum = num1 + num2;

    ListNode *res = new ListNode(sum % 10);
    ListNode *cur = res;
    sum /= 10;

    while (sum > 0) {
      ListNode *node = new ListNode(sum % 10);
      cur->next = node;
      cur = node;
      sum /= 10;
    }
    return res;
  }
};

int main() {
  Solution sol;
  // ListNode *Nodea4 = new ListNode(7);
  ListNode *Nodea3 = new ListNode(3);
  ListNode *Nodea2 = new ListNode(4, Nodea3);
  ListNode *Nodea1 = new ListNode(2, Nodea2);

  ListNode *Nodeb3 = new ListNode(4);
  ListNode *Nodeb2 = new ListNode(6, Nodeb3);
  ListNode *Nodeb1 = new ListNode(5, Nodeb2);

  ListNode *result = sol.addTwoNumbers(Nodea1, Nodeb1);

  while (result) {
    cout << result->val << endl;
    result = result->next;
  }

  return 0;
}