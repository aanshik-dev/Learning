// Given a singly linked list, write a function to traverse and print its elements in reverse order without modifying the list.
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
   int data;
   struct Node *next;
} node, *nptr;

void revPrt(nptr head);

int main() {

   nptr head, second, third, fourth, fifth;
   head = (nptr)malloc(sizeof(node));
   second = (nptr)malloc(sizeof(node));
   third = (nptr)malloc(sizeof(node));
   fourth = (nptr)malloc(sizeof(node));
   fifth = (nptr)malloc(sizeof(node));

   head->data = 1;
   second->data = 2;
   third->data = 3;
   fourth->data = 4;
   fifth->data = 5;

   head->next = second;
   second->next = third;
   third->next = fourth;
   fourth->next = fifth;
   fifth->next = NULL;

   printf("\nOriginal: ");
   nptr temp = head;
   while (temp != NULL) {
      printf("%d ", temp->data);
      temp = temp->next;
   }
   printf("\nReverse: ");
   revPrt(head);
   printf("\n\n");

   return 0;
}

void revPrt(nptr head) {
   if (head == NULL) {
      return;
   }
   revPrt(head->next);
   printf("%d ", head->data);
   return;
}