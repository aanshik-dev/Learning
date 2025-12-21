// Write a C program to evaluate the following postfix expression using stack. 12,7,3,-,/,2,1,5,+,*,+
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   struct node *prev;
   int data;
} node, *nptr;

// inserts new node
void push(nptr *top, int val) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = val;
   temp->prev = *top;
   *top = temp;
}

// deletes top node and fixes value to variable
void pop(nptr *top, int *n) {
   if (*top == NULL)
      return;
   *n = (*top)->data;
   nptr del = *top;
   *top = (*top)->prev;
   free(del);
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
   nptr top = NULL;
   char str[50];
   int flag = 0;
   printf("\nPlease enter a string with a postfix expression: ");
   scanf(" %s", str);
   printf("\nInput String: \"%s\"\n", str);

   // 12,7,3,-,/,2,1,5,+,*,+
   for (int i = 0; str[i] != '\0'; i++) {
      char c = str[i];
      int num = 0;
      if (c >= '0' && c <= '9') {
         for (i; str[i] != ',' && str[i] != '\0'; i++) {
            num = num * 10 + (str[i] - '0');
         }
         push(&top, num);
         flag++;
      } else if (c == '+' || c == '-' || c == '*' || c == '/') {
         if (flag < 2) {
            printf("String is not well formed\n\n");
            freeStack(top);
            return 0;
         }
         int a, b;
         pop(&top, &b);
         pop(&top, &a);
         flag -= 2;

         if (c == '+')
            push(&top, a + b);
         else if (c == '-')
            push(&top, a - b);
         else if (c == '*')
            push(&top, a * b);
         else if (c == '/')
            push(&top, a / b);
         flag++;
      }
   }

   if (flag != 1) {
      printf("String is not well formed\n\n");
      freeStack(top);
      return 0;
   }
   printf("Result of the postfix expression: [ %d ]\n\n", top->data);
   freeStack(top);
   return 0;
}
