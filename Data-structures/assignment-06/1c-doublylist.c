#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   struct node *prev;
   int data;
   struct node *next;
} node, *nptr;

nptr head = NULL;

void addNode(int val) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = val;
   temp->next = temp;
   temp->prev = temp;
   if (head) {
      temp->prev = head->prev;
      temp->next = head;
      head->prev->next = temp;
      head->prev = temp;
   }
   head = temp;
}

void printList(int dir) {
   if (head) {
      if (dir == 1) {
         nptr cur = head;
         do {
            printf(" %d ", cur->data);
            cur = cur->next;
         } while (cur != head);
      } else if (dir == 2) {
         nptr cur = head->prev;
         do {
            printf(" %d ", cur->data);
            cur = cur->prev;
         } while (cur != head->prev);
      }
   }
}

int main() {
   printf("\nType data in format \"+ <value>\" to add Node. Enter any character to exit.\n");
   while (1) {
      int val;
      char choice;
      printf("Enter Value: ");
      scanf(" %c", &choice);
      if (choice == '+') {
         scanf(" %d", &val);
         addNode(val);
      } else {
         break;
      }
   }

   printf("\nDoubly Linked List\n");
   printf("In Forward order: ");
   printList(2);
   printf("\nIn Reverse order: ");
   printList(1);
   printf("\n");

   return 0;
}