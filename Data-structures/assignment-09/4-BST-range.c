#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   struct node *left, *right;
} node, *nptr;

nptr root = NULL;

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

void prtRange(nptr root, int min, int max) {
   if (root == NULL)
      return;
   if (min < root->data)
      prtRange(root->left, min, max);
   if (min <= root->data && root->data <= max)
      printf("%d ", root->data);
   if (max > root->data)
      prtRange(root->right, min, max);
}

int main() {

   int arr[] = {12, 6, 15, 3, 10, 18, 7, 16};
   for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
      insertNode(&root, arr[i]);
   }

   int min, max;
   printf("Enter minimum value: ");
   scanf("%d", &min);
   printf("Enter maximum value: ");
   scanf("%d", &max);
   prtRange(root, min, max);

   return 0;
}