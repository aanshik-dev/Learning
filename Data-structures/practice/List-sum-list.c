#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   struct node *next;
} node, *nptr;

// inserts new node at the beginning and returns updated head.
nptr addNode(nptr head, int val) {
   nptr cur = head;
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = val;
   temp->next = NULL;
   if (cur != NULL) {
      temp->next = cur;
   } else
      cur = temp;
   return temp;
}

void freeList(nptr head) {
   nptr temp;
   while (head != NULL) {
      temp = head;
      head = head->next;
      free(temp);
   }
}

int main() {
   // initialise 3 head for 3 linked list
   nptr head1 = NULL, head2 = NULL, head3 = NULL;
   // size of linked list
   int s1, s2;
   // taking linked list 1 as user input
   printf("\nEnter size of first link list: ");
   scanf(" %d", &s1);
   for (int i = 0; i < s1; i++) {
      printf("Enter digit [%d]: ", i);
      int val;
      scanf(" %d", &val);
      if (val < 10 && val >= 0)
         head1 = addNode(head1, val);
      else {
         printf("\nPlease enter single digit.\n\n");
         return 0;
      }
   }

   // taking linked list 2 as user input
   printf("\nEnter size of second link list: ");
   scanf(" %d", &s2);
   for (int i = 0; i < s2; i++) {
      printf("Enter digit [%d]: ", i);
      int val;
      scanf(" %d", &val);
      if (val < 10 && val >= 0)
         head2 = addNode(head2, val);
      else {
         printf("\nPlease enter single digit.\n\n");
         return 0;
      }
   }

   nptr temp1 = head1, temp2 = head2;
   int size = s1 > s2 ? s1 : s2;
   int carry = 0;
   for (int i = 0; i < size; i++) {
      int sum = 0;
      if (temp1 != NULL) { // If link list 1 ends then nothing added
         sum += temp1->data;
         temp1 = temp1->next;
      }
      if (temp2 != NULL) { // If link list 2 ends then nothing added
         sum += temp2->data;
         temp2 = temp2->next;
      }
      sum += carry; // adds the carry
      if (sum / 10 != 0) {
         carry = 1; // if sum greater than 9 then carry +1
         sum = sum % 10;
      } else {
         carry = 0; // if not reset carry to 0
      }
      head3 = addNode(head3, sum); // adds sum digit to list 3
      sum = 0;
   }
   if (carry == 1) {
      head3 = addNode(head3, 1); // adds endcarry
   }

   nptr temp; // Prints the summation linked list
   printf("\nSummation Link List: ");
   temp = head3;
   while (temp != NULL) {
      printf(" %d ", temp->data);
      temp = temp->next;
   }
   printf("\n\n");
   freeList(head1);
   freeList(head2);
   freeList(head3);

   return 0;
}