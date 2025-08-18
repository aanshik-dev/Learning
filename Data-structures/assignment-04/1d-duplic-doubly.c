#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   struct node *prev;
   int data;
   struct node *next;
} node, *nptr;

nptr insertNode(nptr last, int data) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = data;
   last->next = temp;
   temp->prev = last;
   temp->next = NULL;
   return temp;
}

void delCopy(nptr head) {
   nptr test = head, iter = NULL;
   while (test != NULL) {
      iter = test->next;
      while (iter != NULL) {
         if (test->data == iter->data) {
            iter->prev->next = iter->next;
            if (iter->next != NULL) {
               iter->next->prev = iter->prev;
            }
            free(iter);
         }
         iter = iter->next;
      }
      test = test->next;
   }
}

int main() {

   nptr head = (nptr)malloc(sizeof(node));
   head->prev = NULL;
   head->next = NULL;
   head->data = 1;
   nptr last = head;

   last = insertNode(last, 1);
   last = insertNode(last, 1);
   last = insertNode(last, 4);
   last = insertNode(last, 5);
   last = insertNode(last, 4);
   last = insertNode(last, 9);
   last = insertNode(last, 8);
   last = insertNode(last, 7);
   last = insertNode(last, 7);

   nptr temp = head;
   printf("\nInitial link list\n");
   while (temp != NULL) {
      printf(" %d ", temp->data);
      temp = temp->next;
   }
   printf("\n\n");
   delCopy(head);
   temp = head;
   printf("\nFinal link list\n");
   while (temp != NULL) {
      printf(" %d ", temp->data);
      temp = temp->next;
   }
   printf("\n\n");

   return 0;
}