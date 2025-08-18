#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   struct node *left, *right;
} node, *nptr;

nptr root1 = NULL, root2 = NULL;

void insertNode(nptr *r, int n) {
   if (*r == NULL) {
      *r = (nptr)malloc(sizeof(node));
      (*r)->data = n;
      (*r)->left = (*r)->right = NULL;
   } else if (n < (*r)->data) {
      insertNode(&(*r)->left, n);
   } else if (n > (*r)->data) {
      insertNode(&(*r)->right, n);
   }
}

int isSame(int n, nptr r2) {
   if (r2 != NULL) {
      int flag = 0;
      if (n == r2->data) {
         flag = 1;
      } else if (n < r2->data) {
         flag = isSame(n, r2->left);
      } else if (n > r2->data) {
         flag = isSame(n, r2->right);
      }
      return flag;
   } else {
      return 0;
   }
}

int flag = 1;
void inOrderCheck(nptr r) {
   if (r != NULL) {
      inOrderCheck(r->left);
      if (flag == 1) {
         flag = isSame(r->data, root2);
         if (flag == 1)
            inOrderCheck(r->right);
         else {
            return;
         }
      } else {
         return;
      }
   }
}

int main() {

   printf("Please enter the value in the format \"+ <number>\" to insert node and any other key to exit\n");
   int n;
   char c;
   printf("Enter BST 1 !!\n");
   while (1) {
      printf("Enter Value: ");
      scanf(" %c", &c);
      if (c == '+') {
         scanf(" %d", &n);
         insertNode(&root1, n);
      } else {
         break;
      }
   }
   printf("Enter BST 2 !!\n");
   while (1) {
      printf("Enter Value: ");
      scanf(" %c", &c);
      if (c == '+') {
         scanf(" %d", &n);
         insertNode(&root2, n);
      } else {
         break;
      }
   }

   if (root1 == NULL && root2 == NULL) {
      return 1;
   } else if (root1 == NULL || root2 == NULL) {
      return 0;
   } else {
      inOrderCheck(root1);
      if (flag == 1) {
         printf("Both BST have same Elements !!\n");
      } else {
         printf("Both BST have different Elements !!\n");
      }
   }

   return 0;
}

