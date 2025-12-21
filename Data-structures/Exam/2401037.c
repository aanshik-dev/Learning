#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
   char data[50];
   struct node *left, *right;
   int height;
} node, *nptr;

typedef struct str {
   char data[50];
} str, *sptr;

int size = 0;
str strarr[50];

int height(nptr node) {
   if (node == NULL) {
      return 0;
   }
   return node->height;
}

int max(nptr n1, nptr n2) {
   int x = height(n1);
   int y = height(n2);
   return x > y ? x : y;
}

int getBal(nptr node) {
   if (node == NULL) {
      return 0;
   }
   return height(node->left) - height(node->right);
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

nptr root = NULL;

void avlAdd(nptr *r, char str[]) {
   if (*r == NULL) {
      *r = (nptr)malloc(sizeof(node));
      strcpy((*r)->data, str);
      (*r)->height = 1;
      (*r)->left = (*r)->right = NULL;
      return;
   } else if (strcmp(str, (*r)->data) < 0) {
      avlAdd(&(*r)->left, str);
   } else if (strcmp(str, (*r)->data) > 0) {
      avlAdd(&(*r)->right, str);
   }

   (*r)->height = max((*r)->left, (*r)->right) + 1;
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

void nodePrt(nptr node) {
   if (node == NULL) {
      return;
   }
   if (node->left != NULL) {
      printf(" %s <-", node->left->data);
   }
   printf(" %s ", node->data);
   if (node->right != NULL) {
      printf("-> %s ", node->right->data);
   }
   printf("\n");
}

void inOrderPrt(nptr r) {
   if (r == NULL) {
      return;
   }
   inOrderPrt(r->left);
   nodePrt(r);
   inOrderPrt(r->right);
}

void inOrder(nptr r) {
   if (r == NULL) {
      return;
   }
   inOrder(r->left);
   strcpy(strarr[size++].data, r->data);
   printf(" \"%s\" ", r->data);
   inOrder(r->right);
}
void preOrder(nptr r) {
   if (r == NULL) {
      return;
   }
   printf(" \"%s\" ", r->data);
   preOrder(r->left);
   preOrder(r->right);
}
void postOrder(nptr r) {
   if (r == NULL) {
      return;
   }
   postOrder(r->left);
   postOrder(r->right);
   printf(" \"%s\" ", r->data);
}

void near(char word[], int k) {
   int j = 0;
   if (size == 0) {
      return;
   }
   while (!strcmp(word, strarr[j].data)) {
   }
}

int main() {
   printf("\nPlease enter input in the form \" + <string> \" to add and any character to exit.\n");
   while (1) {
      char str[50];
      char c;
      printf("\nInput : ");
      scanf(" %c", &c);
      if (c == '+') {
         scanf(" %s", str);
         avlAdd(&root, str);
         printf("string added successfully !!\n");
         printf("Current Tree in Inorder Format(Left Child <-- node --> roght child)\n");
         inOrderPrt(root);
      } else {
         break;
      }
   }

   printf("\nInOrder: ");
   inOrder(root);
   printf("\nPreOrder: ");
   preOrder(root);
   printf("\nPostOreder: ");
   postOrder(root);
   printf("\n");

   char node[50];
   int k = 0;
   printf("Please enter node to find neighbours : ");
   scanf(" %s", node);
   printf("Enter the diameter: ");
   scanf(" %d", &k);

   printf("\n\n");
}