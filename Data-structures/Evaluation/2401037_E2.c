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
      return;
   }
   newNode->data = val;
   newNode->prev = *top;
   *top = newNode;
}

nptr top = NULL;

int maxlen(char str[]) {
   int n = 0, temp = 0;
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
   return temp > n ? temp : n;
}

int main() {
   char str[50];
   printf("\nPlease Enter a String: ");
   scanf(" %s", str);
   printf("Entered String: %s\n", str);
   int len = strlen(str);
   int result = 0;
   result = maxlen(str);


   char tempstr[50];
   for (int i = 0; i < len; i++) {
      strcpy(tempstr, str);
      for (int j = i; j < len; j++) {
         tempstr[j] = tempstr[j + 1];
      }
      int num = maxlen(tempstr);
      result = num > result ? num : result;
   }
   printf("Output: %d", result);

   return 0;
}