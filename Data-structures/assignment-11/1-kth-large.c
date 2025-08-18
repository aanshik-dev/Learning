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

void inOrder(nptr r, int arr[]) {
   static int i = 0;
   if (r == NULL) {
      return;
   }
   inOrder(r->left, arr);
   arr[i++] = r->data;
   inOrder(r->right, arr);
}

int main() {
   int bst[] = {50, 30, 20, 40, 70, 60, 80};
   int n = sizeof(bst) / sizeof(bst[0]);
   for (int i = 0; i < n; i++) {
      insertNode(&root, bst[i]);
   }
   inOrder(root, bst);

   int k;
   printf("\nPlease enter the Kth Position to find the Largest Element: ");
   scanf("%d", &k);

   if (k > n || k < 1) {
      printf("\nInvalid Input !!\n\n");
      return 0;
   }

   printf("\nInorder Traversal: ");
   for (int i = 0; i < n; i++) {
      printf(" %d ", bst[i]);
   }

   printf("\nLargest Element at Position %d: %d\n\n", k, bst[n - k]);

   return 0;
}