#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
   int data;
   struct Node *next;
} node, *nptr;

void addNode(nptr *head, int data);
void insertNode(nptr *head, int data);
void freeList(nptr *head);

int main() {
   nptr head = NULL;
   addNode(&head, 0);
   addNode(&head, 3);
   addNode(&head, 5);
   addNode(&head, 8);
   addNode(&head, 9);
   addNode(&head, 12);
   addNode(&head, 17);

   int val;
   printf("Enter value to insert: ");
   scanf("%d", &val);

   printf("\nInitial Linked List: ");
   nptr temp = head;
   while (temp != NULL) {
      printf("%d ", temp->data);
      temp = temp->next;
   }
   printf("\n");

   insertNode(&head, val);

   printf("\nFinal Linked List: ");
   temp = head;
   while (temp != NULL) {
      printf("%d ", temp->data);
      temp = temp->next;
   }
   printf("\n\n");
   freeList(&head);
   return 0;
}

void addNode(nptr *head, int data) {
   nptr newNode = (nptr)malloc(sizeof(node));
   if (newNode == NULL) {
      printf("Memory not allocated.\n");
      return;
   }
   newNode->data = data;
   newNode->next = NULL;

   if (*head == NULL) {
      *head = newNode;
      return;
   }
   nptr temp = *head;
   while (temp->next != NULL) {
      temp = temp->next;
   }
   temp->next = newNode;
}

void insertNode(nptr *head, int data) {
   nptr new = (nptr)malloc(sizeof(node));
   if (new == NULL) {
      printf("Memory not allocated.\n");
      return;
   }
   new->data = data;
   new->next = NULL;

   if (*head == NULL || data < (*head)->data) {
      new->next = *head;
      *head = new;
      return;
   }
   nptr temp = *head;
   while (temp->next != NULL && data > temp->next->data) {
      temp = temp->next;
   }
   new->next = temp->next;
   temp->next = new;
}

void freeList(nptr *head) {
   nptr temp;
   while (*head != NULL) {
      temp = *head;
      *head = (*head)->next;
      free(temp);
   }
}