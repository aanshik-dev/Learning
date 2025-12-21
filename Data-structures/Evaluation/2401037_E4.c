#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   struct node *left, *right;
} node, *nptr;

nptr root1 = NULL;
nptr root2 = NULL;
nptr intRoot = NULL;

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

void inOrder(nptr *r) {
   if (*r == NULL) {
      return;
   }
   inOrder(&(*r)->left);
   printf("%d ", (*r)->data);
   inOrder(&(*r)->right);
}

void uniBST(nptr *bst1, nptr *bst2) {
   if (*bst2 == NULL) {
      return;
   }
   uniBST(&(*bst1), &(*bst2)->left);
   insertNode(&root1, (*bst2)->data);
   uniBST(&(*bst1), &(*bst2)->right);
}

int searchBST(nptr *r, int key) {
   if (*r == NULL) {
      return 0;
   }
   if (key < (*r)->data) {
      searchBST(&(*r)->left, key);
   } else if (key > (*r)->data) {
      searchBST(&(*r)->right, key);
   } else {
      return 1;
   }
}

void intBST(nptr *bst1, nptr *bst2) {
   if (*bst2 == NULL) {
      return;
   }
   intBST(&(*bst1), &(*bst2)->left);
   if (searchBST(&root1, (*bst2)->data)) {
      insertNode(&intRoot, (*bst2)->data);
   }
   intBST(&(*bst1), &(*bst2)->right);
}

int main() {
   int n, m, key;
   printf("Enter the number of nodes in the first BST: ");
   scanf("%d", &n);
   printf("Please Enter the nodes of BST: ");
   for (int i = 0; i < n; i++) {
      scanf("%d", &key);
      insertNode(&root1, key);
   }
   printf("\n");

   printf("Enter the number of nodes in the Second BST: ");
   scanf("%d", &m);
   printf("Please Enter the nodes of BST: ");
   for (int i = 0; i < m; i++) {
      scanf("%d", &key);
      insertNode(&root2, key);
   }
   printf("\n");

   printf("BST1 Inorder : ");
   inOrder(&root1);
   printf("\n");

   printf("BST2 Inorder : ");
   inOrder(&root2);
   printf("\n");

   intBST(&root1, &root2);
   printf("Intersection Inorder : ");
   inOrder(&intRoot);
   printf("\n");

   uniBST(&root1, &root2);
   printf("Union Inorder: ");
   inOrder(&root1);
   printf("\n\n");

   return 0;
}

// 10 5 20 3 15 7 25
// 8 25 3 15 30