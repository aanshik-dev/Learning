#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   struct node *next;
} node, *nptr;

// inserts new node and returns updated head
nptr addNode(nptr head, int post, int val) {
   nptr cur = head;
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = val;
   temp->next = NULL;

   if (post == 0) {
      if (cur != NULL) {
         temp->next = cur;
      } else
         cur = temp;
      return temp;
   } else if (post == 1) {
      if (cur != NULL) {
         while (cur->next != NULL) {
            cur = cur->next;
         }
         cur->next = temp;
      } else {
         cur = temp;
         return temp;
      }
      return head;
   }
}

// converts linked list to number
int numConv(nptr head, int size) {
   nptr cur = head;
   int sum = 0;
   if (cur == NULL) {
      return 0;
   }
   for (int i = 0; i < size; i++) {
      sum = sum * 10 + cur->data;
      cur = cur->next;
   }
   return sum;
}

// converts number to linked list
nptr listConv(nptr head, int num) {
   int n = num;
   do {
      int rem = n % 10;
      head = addNode(head, 0, rem);
      n = n / 10;
   } while (n > 0);
   return head;
}

nptr freeList(nptr head) {
   nptr temp;
   while (head != NULL) {
      temp = head;
      head = head->next;
      free(temp);
   }
   return head;
}

nptr listIn(nptr head, int s) {
   nptr temp = head;
   for (int i = 0; i < s; i++) {
      printf("Enter digit [%d]: ", i + 1);
      int val;
      scanf(" %d", &val);
      if (val < 10 && val >= 0)
         temp = addNode(temp, 1, val);
      else {
         printf("\nPlease enter single digit.\n\n");
         freeList(temp);
         return NULL;
      }
   }
   return temp;
}

int main() {
   // initialise 3 head for 3 linked list
   nptr head1 = NULL, head2 = NULL, head3 = NULL;
   // size of linked list
   int s1, s2;
   // taking linked list 1 as user input
   printf("\nEnter size of first link list: ");
   scanf(" %d", &s1);
   head1 = listIn(head1, s1);

   // taking linked list 2 as user input
   printf("\nEnter size of second link list: ");
   scanf(" %d", &s2);
   head2 = listIn(head2, s2);

   nptr temp;
   printf("\nLinked list 1: ");
   temp = head1;
   while (temp != NULL) {
      printf(" %d", temp->data);
      temp = temp->next;
   }
   printf("\nLinked list 2: ");
   temp = head2;
   while (temp != NULL) {
      printf(" %d", temp->data);
      temp = temp->next;
   }

   // Converting linked list to number
   int num1 = numConv(head1, s1);
   int num2 = numConv(head2, s2);
   int sum = num1 + num2;
   // Converting number to linked list
   head3 = listConv(head3, sum);

   // Prints the summation linked list
   printf("\n\nSummation Link List: ");
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