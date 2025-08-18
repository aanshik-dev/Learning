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

int checkBST(nptr root) {
   if (root == NULL) {
      return 1;
   }
   if (root->left != NULL && root->left->data > root->data) {
      return 0;
   }
   if (root->right != NULL && root->right->data < root->data) {
      return 0;
   }
   return checkBST(root->left) && checkBST(root->right);
}

/*
      15
   8      20
3  10  17    25
*/

int main() {
   printf("Enter the Root Node: ");
   int n;
   scanf("%d", &n);
   if (n != -1) {
      root = (nptr)malloc(sizeof(node));
      root->data = n;
      printf("Enter Left Child of %d: ", n);
      root->left = treein();
      printf("Enter right Child of %d: ", n);
      root->right = treein();
   }

   if (checkBST(root)) {
      printf("This is a BST !!\n");
   } else {
      printf("This is not a BST !!\n");
   }

   return 0;
}