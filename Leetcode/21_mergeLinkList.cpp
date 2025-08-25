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
  ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {

    if (list1 == nullptr) {
      return list2;
    } else if (list2 == nullptr) {
      return list1;
    } else if (list1->val < list2->val) {
      list1->next = mergeTwoLists(list1->next, list2);
      return list1;
    } else {
      list2->next = mergeTwoLists(list1, list2->next);
      return list2;
    }
  }
};

int main() {

  Solution sol;
  ListNode *Nodea1 = new ListNode(16);
  ListNode *Nodea2 = new ListNode(13, Nodea1);
  ListNode *Nodea3 = new ListNode(10, Nodea2);
  ListNode *Nodea4 = new ListNode(8, Nodea3);
  ListNode *Nodea5 = new ListNode(7, Nodea4);
  ListNode *Nodea6 = new ListNode(3, Nodea5);
  ListNode *Nodea7 = new ListNode(1, Nodea6);


  ListNode *Nodeb1 = new ListNode(12);
  ListNode *Nodeb2 = new ListNode(6, Nodeb1);
  ListNode *Nodeb3 = new ListNode(4, Nodeb2);
  ListNode *Nodeb4 = new ListNode(3, Nodeb3);
  ListNode *Nodeb5 = new ListNode(2, Nodeb4);


  sol.mergeTwoLists(Nodea7, Nodeb5);

  return 0;
}