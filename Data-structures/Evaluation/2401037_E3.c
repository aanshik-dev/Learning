#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   struct node *left, *right;
} node, *nptr;

nptr root = NULL;

nptr treein() {
   int n;
   scanf("%d", &n);
   if (n == -1)
      return NULL;
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = n;
   printf("Enter Left Child of %d: ", n);
   temp->left = treein();
   printf("Enter Right Child of %d: ", n);
   temp->right = treein();
   return temp;
}

void inOrder(nptr r) {
   if (r == NULL) {
      return;
   }
   printf(" %d ", r->data);
   inOrder(r->left);
   inOrder(r->right);
}

int leaf = 0;
void nodeCount(nptr r) {
   if (r == NULL) {
      return;
   }
   nodeCount(r->left);
   if (r->left == NULL && r->right == NULL) {
      leaf++;
      printf(" %d ", r->data);
      return;
   }
   nodeCount(r->right);
}

int main() {

   // 50 20 10 -1 -1 30 -1 50 18 -1 -1 23 -1 -1 60 80 -1 -1 70 -1 -1
   printf("Enter the Root Node: ");
   int n;
   scanf("%d", &n);
   if (n != -1) {
      root = (nptr)malloc(sizeof(node));
      root->data = n;
      printf("Enter Left Child of %d: ", n);
      root->left = treein();
      printf("Enter Right Child of %d: ", n);
      root->right = treein();
   }

   printf("\n\nInput Tree in inorder: ");
   inOrder(root);
   printf("\n\nLeaf of tree are : ");
   nodeCount(root);
   printf("\nTotal Leaf Nodes : %d ", leaf);
   printf("\n\n");
   return 0;
}