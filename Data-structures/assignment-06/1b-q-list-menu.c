#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   struct node *next;
} node, *nptr;

nptr top = NULL, end = NULL;

void deq() {
   if (end == NULL) {
      printf("Queue is Empty !!\n");
      return;
   } else if (end == top) {
      printf("Dequeued Value: %d\n", end->data);
      free(end);
      end = NULL;
      top = NULL;
      return;
   } else {
      top->next = end->next;
      printf("Dequeued Value: %d\n", end->data);
      free(end);
      end = top->next;
   }
}

void enq(int val) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = val;
   if (end == NULL) {
      end = temp;
      top = temp;
   }
   temp->next = end;
   top->next = temp;
   top = temp;
}

void freelist(nptr temp) {
   if (temp == NULL) {
      return;
   }
   freelist(temp->next);
   free(temp);
}

int main() {
   do {
      int choice;
      printf("\n *************** MENU ***************\n [1. Enqueue] [2. Dequeue] [3. Exit]\n\n");
      printf("Please choose an option: ");
      scanf("%d", &choice);

      if (choice == 1) {
         int n;
         printf("Enter a value to Enqueue: ");
         scanf("%d", &n);
         enq(n);
      } else if (choice == 2) {
         deq();
      } else if (choice == 3) {
         printf("Terminating...\n\n");
         break;
      } else {
         printf("Please enter a valid choice.\n");
      }
      nptr temp = end;
      printf("Current Queue: [ ");
      do {
         if (temp == NULL)
            break;
         printf("%d ", temp->data);
         temp = temp->next;
      } while (temp != end);
      printf("]\n");

   } while (1);

   freelist(end);
   return 0;
}
