// Write a C program to check whether a string of opening and closing parenthesis is well formed or not using stack
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   struct node *prev;
   int data;
} node, *nptr;

void push(nptr *top, int val) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = val;
   temp->prev = *top;
   *top = temp;
}

char pop(nptr *top) {
   if (*top == NULL) {
      return '\0';
   }
   char ret = (*top)->data;
   nptr del = *top;
   *top = (*top)->prev;
   free(del);
   return ret;
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

int main() {
   nptr top = NULL;
   char str[50];
   printf("\nPlease enter a string containing brackets: ");
   scanf(" %s", str);
   printf("\nInput String: \"%s\"\n", str);

   for (int i = 0; str[i] != '\0'; i++) {
      char c = str[i];
      if (c == '(' || c == '{' || c == '[') {
         push(&top, c);
      } else if (c == ')' || c == '}' || c == ']') {
         char brac = pop(&top);
         if (brac == '\0' || (c == ')' && brac != '(') || (c == '}' && brac != '{') || (c == ']' && brac != '[')) {
            printf("String is not well formed\n\n");
            return 0;
         }
      }
   }
   printf("String is well formed\n\n");
   freeStack(top);
   return 0;
}
