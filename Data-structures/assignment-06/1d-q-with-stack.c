#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   struct node *prev;
} node, *nptr;

nptr stack1 = NULL, stack2 = NULL;

void push(nptr *top, int val) {
   nptr temp = (nptr)malloc(sizeof(node));
   if (temp == NULL) {
      printf("Memory allocation failed.\n");
      return;
   }
   temp->data = val;
   temp->prev = *top;
   *top = temp;
}

void pop(nptr *top) {
   if (*top == NULL) {
      return;
   }
   nptr temp = *top;
   *top = (*top)->prev;
   free(temp);
}

void enq(int n) {
   push(&stack1, n);
}

void deq() {
   if (stack1 == NULL && stack2 == NULL) {
      printf("Queue is empty.\n");
      return;
   } else if (stack2 == NULL) {
      while (stack1 != NULL) {
         push(&stack2, stack1->data);
         pop(&stack1);
      }
      printf("Dequeued Value: %d\n", stack2->data);
      pop(&stack2);

   } else {
      printf("Dequeued Value: %d\n", stack2->data);
      pop(&stack2);
   }
}

void freeStack(nptr top) {
   if (top == NULL) {
      return;
   }
   freeStack(top->prev);
   free(top);
}

void prtstk(nptr top, int flag) {
   if (top == NULL) {
      return;
   }
   if (flag == 0) {
      printf("%d ", top->data);
      prtstk(top->prev, flag);
   } else {
      prtstk(top->prev, flag);
      printf("%d ", top->data);
   }
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

      printf("Stack 1: [ ");
      prtstk(stack1, 1);
      printf("]\n");
      printf("Stack 2: [ ");
      prtstk(stack2, 1);
      printf("]\n");
      printf("Current Queue: [ ");
      prtstk(stack2, 0);
      prtstk(stack1, 1);
      printf("]\n");

   } while (1);

   freeStack(stack1);
   freeStack(stack2);

   return 0;
}