#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   int height;
   struct node *left, *right;
} node, *nptr;
#include "../printTree.c"

nptr root = NULL;

int getHeight(nptr node) {
   if (node == NULL) {
      return 0;
   }
   return node->height;
}

int getBal(nptr node) {
   if (node == NULL) {
      return 0;
   }
   return getHeight(node->left) - getHeight(node->right);
}

int max(nptr n1, nptr n2) {
   int a = getHeight(n1);
   int b = getHeight(n2);
   return a > b ? a : b;
}

void rightRotate(nptr *pivot) {
   nptr subtree = (*pivot)->left;
   nptr temp = subtree->right;

   subtree->right = *pivot;
   (*pivot)->left = temp;
   *pivot = subtree;

   subtree = (*pivot)->right;
   subtree->height = max(subtree->left, subtree->right) + 1;
   (*pivot)->height = max((*pivot)->left, (*pivot)->right) + 1;
}

void leftRotate(nptr *pivot) {
   nptr subtree = (*pivot)->right;
   nptr temp = subtree->left;

   subtree->left = *pivot;
   (*pivot)->right = temp;
   *pivot = subtree;

   subtree = (*pivot)->left;
   subtree->height = max(subtree->left, subtree->right) + 1;
   (*pivot)->height = max((*pivot)->left, (*pivot)->right) + 1;
}

void avlInsert(nptr *r, int data) {
   if ((*r) == NULL) {
      *r = (nptr)malloc(sizeof(node));
      (*r)->data = data;
      (*r)->height = 1;
      (*r)->left = (*r)->right = NULL;
      return;
   }
   if (data < (*r)->data) {
      avlInsert(&(*r)->left, data);
   } else if (data > (*r)->data) {
      avlInsert(&(*r)->right, data);
   }
   (*r)->height = 1 + max((*r)->left, (*r)->right);
   int bf = getBal(*r);

   if (bf > 1) {
      if (getBal((*r)->left) >= 0) {
         rightRotate(r);
      } else {
         leftRotate(&(*r)->left);
         rightRotate(r);
      }
   } else if (bf < -1) {
      if (getBal((*r)->right) <= 0) {
         leftRotate(r);
      } else {
         rightRotate(&(*r)->right);
         leftRotate(r);
      }
   }
}
nptr inPred(nptr r) {
   r = r->left;
   while (r->right != NULL) {
      r = r->right;
   }
   return r;
}

void avlDelete(nptr *r, int n) {
   if (*r == NULL) {
      printf("Node not found !!\n");
      return;
   }
   if (n < (*r)->data) {
      avlDelete(&(*r)->left, n);
   } else if (n > (*r)->data) {
      avlDelete(&(*r)->right, n);
   } else {
      if ((*r)->left == NULL) {
         nptr temp = *r;
         *r = (*r)->right;
         free(temp);
         printf("Node deleted Successfully !!\n");
         return;
      } else if ((*r)->right == NULL) {
         nptr temp = *r;
         *r = (*r)->left;
         free(temp);
         printf("Node deleted Successfully !!\n");
         return;
      } else {
         nptr iPre = inPred(*r);
         (*r)->data = iPre->data;
         avlDelete(&(*r)->left, iPre->data);
      }
   }

   (*r)->height = max((*r)->left, (*r)->right) + 1;
   int bf = getBal(*r);

   if (bf > 1) {
      if (getBal((*r)->left) >= 0) {
         rightRotate(r); // LL
      } else {
         leftRotate(&(*r)->left);
         rightRotate(r); // LR
      }
   } else if (bf < -1) {
      if (getBal((*r)->right) <= 0) {
         leftRotate(r); // RR
      } else {
         rightRotate(&(*r)->right);
         leftRotate(r); // RL
      }
   }
}

int searchNode(nptr r, int n) {
   if (r == NULL) {
      return 0;
   } else if (r->data == n) {
      return 1;
   } else if (n < r->data) {
      return searchNode(r->left, n);
   } else if (n > r->data) {
      return searchNode(r->right, n);
   }
}

void inOrder(nptr r) {
   if (r == NULL) {
      return;
   }
   inOrder(r->left);
   printf(" %d ", r->data);
   inOrder(r->right);
}

void preOrder(nptr r) {
   if (r == NULL) {
      return;
   }
   printf(" %d ", r->data);
   preOrder(r->left);
   preOrder(r->right);
}

void balFactor(nptr r) {
   if (r == NULL) {
      return;
   }
   balFactor(r->left);
   printf(" %d[%d] ", r->data, getBal(r));
   balFactor(r->right);
}

// 50 20 60 10 40 70 5 15 30 45 65 80 25 35 55 75 85
// 1 50 1 20 1 60 1 10 1 40 1 70 1 5 1 15 1 30 1 45 1 65 1 80 1 25 1 35 1 55 1 75 1 85

// 20 60 50 15 45 65 85
// 2 20 4 2 60 4 2 50 4 2 15 4 2 45 4 2 65 4 2 85 4

int main() {
   int choice, key;

   do {
      printf("\n::: >  MENU  < :::\n1. Insert   2. Delete   3. Search   4. Display   5. Display Balance Factor   6. Exit\n");
      printf("\nPlease enter your choice: ");
      scanf("%d", &choice);
      switch (choice) {
      case 1:
         printf("Please enter a value to insert: ");
         scanf("%d", &key);
         avlInsert(&root, key);
         printf("%d added to the tree successfully !!\n");
         break;
      case 2:
         printf("Please enter a value to delete: ");
         scanf("%d", &key);
         avlDelete(&root, key);
         break;
      case 3:
         printf("Please enter a value to search: ");
         scanf("%d", &key);
         if (searchNode(root, key)) {
            printf("%d is present in the tree !!\n");
         } else {
            printf("%d is NOT present in the tree !!\n");
         }
         break;
      case 4:
         printf("\nInorder: ");
         inOrder(root);
         printf("\n");
         printf("Preorder: ");
         preOrder(root);
         printf("\n\n");
         print_tree(root, 10);
         break;
      case 5:
         printf("Balance Factor: ");
         balFactor(root);
         printf("\n");
         break;
      case 6:
         printf("Terminating Execution...\n\n");
         exit(0);
      default:
         printf("Please enter a valid choice.\n");
      }
   } while (1);

   return 0;
}