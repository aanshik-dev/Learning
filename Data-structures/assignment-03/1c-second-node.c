// Write a function in C that prints every second node in a linked list
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
   int data;
   struct Node *next;
} node, *nptr;

int main() {
   nptr head, second, third, fourth, fifth, sixth;
   head = (nptr)malloc(sizeof(node));
   second = (nptr)malloc(sizeof(node));
   third = (nptr)malloc(sizeof(node));
   fourth = (nptr)malloc(sizeof(node));
   fifth = (nptr)malloc(sizeof(node));
   sixth = (nptr)malloc(sizeof(node));

   head->data = 1;
   second->data = 2;
   third->data = 3;
   fourth->data = 4;
   fifth->data = 5;
   sixth->data = 6;

   head->next = second;
   second->next = third;
   third->next = fourth;
   fourth->next = fifth;
   fifth->next = sixth;
   sixth->next = NULL;

   nptr temp = head;
   int i = 1;
   printf("\nEven entries of linked List\n");
   while (temp != NULL) {
      i++;
      temp = temp->next;
      if (i % 2 == 0) {
         printf(" %d ", temp->data);
      }
   }
   printf("\n\n");

   return 0;
}