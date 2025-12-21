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



int main() {

   nptr head = (nptr)malloc(sizeof(node));
   head->prev = NULL;
   head->next = NULL;
   head->data = 1;
   nptr last = head;

   last = insertNode(last, 2);
   last = insertNode(last, 3);
   last = insertNode(last, 4);
   last = insertNode(last, 5);
   last = insertNode(last, 6);
   last = insertNode(last, 7);
   last = insertNode(last, 8);
   
   int post;
   printf("\nEnter the position to split: ");
   scanf(" %d", &post);

   nptr temp = head;
   printf("\n  Parent link list\n      ");
   while (temp != NULL) {
      printf(" %d ", temp->data);
      temp = temp->next;
   }
   printf("\n\n");

   temp = head;
   for (int i = 1; i <= post; i++) {
      temp = temp->next;
   }
   temp->prev->next = NULL;
   temp->prev = NULL;

   nptr temp2 = head;
   printf("  Child link list\n      ");
   while (temp2 != NULL) {
      printf(" %d ", temp2->data);
      temp2 = temp2->next;
   }
   printf("\n      ");
   while (temp != NULL) {
      printf(" %d ", temp->data);
      temp = temp->next;
   }
   printf("\n\n");

   return 0;
}