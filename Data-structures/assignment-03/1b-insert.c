// Write a function in C to insert an item after a given node in a singly linked list
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
   int data;
   struct Node *next;
} node, *nptr;
// [0]->[1]->[2]->[3]->[4]->[5]->NULL
int main() {
   nptr head, first, second, third, fourth, fifth;
   head = (nptr)malloc(sizeof(node));
   first = (nptr)malloc(sizeof(node));
   second = (nptr)malloc(sizeof(node));
   third = (nptr)malloc(sizeof(node));
   fourth = (nptr)malloc(sizeof(node));
   fifth = (nptr)malloc(sizeof(node));

   head->data = 0;
   first->data = 1;
   second->data = 2;
   third->data = 3;
   fourth->data = 4;
   fifth->data = 5;

   head->next = first;
   first->next = second;
   second->next = third;
   third->next = fourth;
   fourth->next = fifth;
   fifth->next = NULL;

   int pos, val;
   printf("Please Enter position to insert: ");
   scanf(" %d", &pos);
   printf("Enter Value to insert: ");
   scanf(" %d", &val);
   nptr new_node = (nptr)malloc(sizeof(node));
   new_node->data = val;

   // prints initial linked list
   printf("\nInitial Link List\n");
   nptr t1 = head->next;
   while (t1 != NULL) {
      printf("%d ", t1->data);
      t1 = t1->next;
   }
   printf("\n");

   // traverse to position
   nptr t2 = head;
   for (int i = 0; i < pos - 1; i++) {
      t2 = t2->next != NULL ? t2->next : t2;
   }
   // inserting node
   new_node->next = t2->next;
   t2->next = new_node;

   // printing final linked list
   printf("\nFinal Link List\n");
   nptr t3 = head->next;
   while (t3 != NULL) {
      printf("%d ", t3->data);
      t3 = t3->next;
   }
   printf("\n");

   return 0;
}