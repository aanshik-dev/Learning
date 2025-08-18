#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
   int data;
   struct node *prev;
} node, *nptr;

int pop(nptr *top) {
   if (*top == NULL) {
      return 0;
   }
   nptr temp = *top;
   int ret = (*top)->data;
   *top = (*top)->prev;
   free(temp);
   return ret;
}

void push(nptr *top, int val) {
   nptr newNode = (nptr)malloc(sizeof(node));
   if (newNode == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(1);
   }
   newNode->data = val;
   newNode->prev = *top;
   *top = newNode;
}

int main() {
   nptr top = NULL;
   int n = 0, temp = 0;
   char str[50];
   printf("\nPlease Enter a String: ");
   scanf(" %s", str);

   for (int i = 0; i < strlen(str); i++) {
      char c = str[i];
      if (c == '(') {
         push(&top, temp);
         if (str[i + 1] == '(') {
            temp = 0;
         }
      } else if (c == ')') {
         if (top == NULL) {
            n = n > temp ? n : temp;
            temp = 0;
            continue;
         }
         int num = pop(&top);
         if (str[i - 1] == ')') {
            temp += num + 2;
         } else {
            temp = num + 2;
         }
      }
   }

   while (top != NULL) {
      int num = pop(&top);
      temp = num > temp ? num : temp;
   }

   printf("\nResult: %d\n", temp > n ? temp : n);
   return 0;
}