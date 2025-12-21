#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   struct node *left, *right;
} node, *nptr;

nptr root = NULL;

node *addNode(int data) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = data;
   temp->left = temp->right = NULL;
   return temp;
}

nptr treeConv(int pre[], int in[], int n) {
   if (n == 0)
      return NULL;
   else {
      nptr temp = addNode(pre[0]);
      int l = 0;
      while (in[l] != pre[0])
         l++;
      temp->left = treeConv(pre + 1, in, l);
      temp->right = treeConv(pre + l + 1, in + l + 1, n - l - 1);
      return temp;
   }
}

int main() {
   int n;
   printf("\nPlease enter number of nodes in tree: ");
   scanf("%d", &n);
   int pre[n], in[n];
   printf("\nPlease enter preorder traversal of tree: ");
   for (int i = 0; i < n; i++) {
      scanf("%d", &pre[i]);
   } // 1 2 3 15 5 8 4 6 7 9 10 11
   printf("\nPlease enter inorder traversal of tree: ");
   for (int i = 0; i < n; i++) {
      scanf("%d", &in[i]);
   } // 3 15 2 5 8 1 6 4 10 9 11 7
   root = treeConv(pre, in, n);

   printf("\nBinary Tree:\n");
   printf("%d ", root->data);                            // 1
   printf("%d ", root->left->data);                      // 2
   printf("%d ", root->right->data);                     // 4
   printf("%d ", root->left->left->data);                // 3
   printf("%d ", root->left->right->data);               // 5
   printf("%d ", root->right->left->data);               // 6
   printf("%d ", root->right->right->data);              // 7
   printf("%d ", root->left->left->right->data);         // 15
   printf("%d ", root->left->right->right->data);        // 8
   printf("%d ", root->right->right->left->data);        // 9
   printf("%d ", root->right->right->left->left->data);  // 10
   printf("%d ", root->right->right->left->right->data); // 11

   return 0;
}