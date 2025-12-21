// Write a C program to convert the following infix expressions into their equivalent postfix as well as prefix expression using stack
// i. (A-B)*(D/E)  --> AB-DE/*  &  *-AB/DE
// ii. A*(B+D)/(E-F*(G+H/K))  --> ABD+*EFGHK/+*-/  & /*A+BD-E*F+G/HK
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
   struct node *prev;
   char data;
} node, *nptr;

nptr top = NULL;

// inserts new node and returns updated head
void push(char val) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = val;
   temp->prev = top;
   top = temp;
}

// deletes top node
void pop() {
   if (top != NULL) {
      nptr temp = top;
      top = top->prev;
      free(temp);
   } else
      return;
}

int pref(char c) {
   if (c == '+' || c == '-')
      return 1;
   else if (c == '*' || c == '/')
      return 2;
   else if (c == '^')
      return 3;
   else
      return 0;
}

void Conv(char str[], char out[], int flag) {
   int j = 0;
   for (int i = 0; str[i] != '\0'; i++) {
      char c = str[i];
      if (c >= 'A' && c <= 'Z') {
         out[j++] = c;
      } else if (c == '(') {
         push(c);
      } else if (c == ')') {
         while (top->data != '(') {
            out[j++] = top->data;
            pop();
         }
         pop();
      } else if (c == '+' || c == '-' || c == '*' || c == '/') {

         while (flag == 1 ? pref(c) <= (top != NULL ? pref(top->data) : 0) : pref(c) < (top != NULL ? pref(top->data) : 0)) {
            out[j++] = top->data;
            pop();
         }
         push(c);
      }
   }

   while (top != NULL) {
      out[j++] = top->data;
      pop();
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

int main() {
   char str[50], out[50], pref = 0;
   printf("\nPlease enter a string with an infix expression: ");
   scanf(" %s", str);
   printf("\nInput String: \" %s \"\n", str);

   int n = strlen(str);
   char prt[n];
   Conv(str, prt, 1);
   printf("\nPostfix Expression: %s\n\n", prt);

   strrev(str);
   for (int i = 0; str[i] != '\0'; i++) {
      if (str[i] == '(')
         str[i] = ')';
      else if (str[i] == ')')
         str[i] = '(';
   }

   Conv(str, prt, 0);
   strrev(prt);
   printf("Prefix Expression: %s\n\n", prt);
   //   /*A+BD-E*F+G/HK
   freeStack(top);
   return 0;
}