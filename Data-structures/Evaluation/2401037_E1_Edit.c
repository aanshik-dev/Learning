#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   struct node *next;
} node, *nptr;

// inserts new node and returns updated head
nptr addNode(nptr head, int val) {
   nptr cur = head;
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = val;
   temp->next = NULL;

   if (cur != NULL) {
      while (cur->next != NULL) {
         cur = cur->next;
      }
      cur->next = temp;
   } else {
      return temp;
   }
   return head;
}

// 1 2 3 2 4 5
void delCopy(int data, nptr h) {
   nptr cur = h;
   int val = data;
   if (cur == NULL || cur->next == NULL) {
      return;
   }
   while (cur->next != NULL) {
      if (val == cur->next->data) {
         nptr temp = cur->next;
         cur->next = cur->next->next;
         free(temp);
      } else {
         cur = cur->next;
      }
   }
}

void crossList(int data, nptr h2) {
   nptr cur = h2;
   int val = data;
   if (cur == NULL) {
      return;
   }
   if (val == cur->data) {
      printf("%d ", val);
      return;
   } else {
      crossList(data, h2->next);
   }
}

void freeList(nptr head) {
   nptr temp = head;
   while (temp != NULL) {
      nptr del = temp;
      temp = temp->next;
      free(del);
   }
}

int main() {

   nptr head1 = NULL, head2 = NULL;
   printf("\nEnter Size of first Link List: ");
   int n1;
   scanf(" %d", &n1);
   for (int i = 0; i < n1; i++) {
      int val;
      printf("Enter digit [%d]: ", i + 1);
      scanf(" %d", &val);
      head1 = addNode(head1, val);
   }

   printf("\nEnter Size of second Link List: ");
   int n2;
   scanf(" %d", &n2);
   for (int i = 0; i < n2; i++) {
      int val;
      printf("Enter digit [%d]: ", i + 1);
      scanf(" %d", &val);
      head2 = addNode(head2, val);
   }

   printf("\nLinked list 1: ");
   nptr temp = head1;
   while (temp != NULL) {
      printf("%d ", temp->data);
      temp = temp->next;
   }
   printf("\n");

   printf("Linked list 2: ");
   temp = head2;
   while (temp != NULL) {
      printf("%d ", temp->data);
      temp = temp->next;
   }
   printf("\n");

   nptr cur = head1;
   while (cur != NULL) {
      delCopy(cur->data, cur);
      cur = cur->next;
   }

   printf("\nIntersection of Link Lists: ");
   cur = head1;
   while (cur != NULL) {
      crossList(cur->data, head2);
      cur = cur->next;
   }
   printf("\n\n");

   freeList(head1);
   freeList(head2);

   return 0;
}
