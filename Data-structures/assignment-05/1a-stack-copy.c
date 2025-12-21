#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   struct node *prev;
   int data;
} node, *nptr;

// inserts new node and returns updated head
void push(nptr *top, int val) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = val;
   temp->prev = *top;
   *top = temp;
}
// deletes top node
int pop(nptr *top) {
   if (*top != NULL) {
      nptr temp = *top;
      int ret = (*top)->data;
      *top = (*top)->prev;
      free(temp);
      return ret;
   } else
      return -1;
}

// duplicates stack using recursion
void dupstack(nptr top, nptr *topC) {
   if (top->prev == NULL) {
      push(topC, top->data);
      return;
   } else {
      dupstack(top->prev, topC);
      push(topC, top->data);
   }
}

// deletes all nodes
void freeStack(nptr top) {
   nptr temp = top;
   while (temp != NULL) {
      nptr del = temp;
      temp = temp->prev;
      free(del);
   }
}

// main
int main() {
   nptr top = NULL, topcopy = NULL;
   printf("\nType data in format \"+ <value>\" to push in stack. Enter any character to exit.\n");
   while (1) {
      int val;
      char choice;
      printf("Enter Value: ");
      scanf(" %c", &choice);
      if (choice == '+') {
         scanf(" %d", &val);
         push(&top, val);
      } else {
         break;
      }
   }

   // duplicating stack
   dupstack(top, &topcopy);

   // printing Stacks
   printf("\nInput Stack\n");
   nptr temp = top;
   while (temp != NULL) {
      printf("[ %02d ]\n", temp->data);
      temp = temp->prev;
   }
   printf("\n");

   printf("Output Stack\n");
   temp = topcopy;
   while (temp != NULL) {
      printf("[ %02d ]\n", temp->data);
      temp = temp->prev;
   }
   printf("\n\n");

   freeStack(top);
   return 0;
}