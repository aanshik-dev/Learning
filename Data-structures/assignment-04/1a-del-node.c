#include <stdio.h>
#include <stdlib.h>
typedef struct node {
   int data;
   struct node *next;
} node, *nptr;

nptr addNode(nptr head, int data) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = data;
   temp->next = NULL;
   if (head == NULL) {
      return temp;
   }

   nptr h = head;
   while (h->next != NULL) {
      h = h->next;
   }
   h->next = temp;
   return head;
}

// 3 2 4 25 6 1 7 9
nptr delNode(nptr head, int post) {
   if (!head) {
      printf("Sorry, the list is empty\n");
      return head;
   }
   nptr temp = head;
   if (post == 1) {
      head = temp->next;
      free(temp);
      return head;
   }
   for (int i = 1; i < post - 1; i++) {
      if (temp->next->next == NULL) {
         printf("This location is invalid\n");
         return head;
      }
      temp = temp->next;
   }
   nptr del = temp->next;
   temp->next = temp->next->next;
   free(del);
   return head;
}

int main() {
   int post;
   nptr head = NULL;
   head = addNode(head, 3);
   head = addNode(head, 2);
   head = addNode(head, 4);
   head = addNode(head, 25);
   head = addNode(head, 6);
   head = addNode(head, 1);
   head = addNode(head, 7);
   head = addNode(head, 9);

   nptr temp = head;
   while (temp != NULL) {
      printf("%d ", temp->data);
      temp = temp->next;
   }

   printf("\nPlease enter position to delete: ");
   scanf("%d", &post);

   head = delNode(head, post);

   temp = head;
   while (temp != NULL) {
      printf("%d ", temp->data);
      temp = temp->next;
   }

   return 0;
}