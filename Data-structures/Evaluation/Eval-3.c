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
   temp->left = treein();
   temp->right = treein();
   return temp;
}

int arr[50];

void path(nptr root, int len) {
   int l = len;
   if (root == NULL) {
      return;
   }
   arr[l++] = root->data;
   path(root->left, l);
   if (root->left == NULL && root->right == NULL) {
      printf(" > ");
      for (int i = 0; i < len + 1; i++) {
         printf("%d ", arr[i]);
      }
      printf("\n");
      return;
   }
   path(root->right, l);
}

//       20
//      /  \ 
//     10   30
//    / \   / \ 
//   5  15 25 35
//  /   /      \ 
// 3  13        33
// 20 10 5 3 -1 -1 -1 15 13 -1 -1 -1 30 25 8 -1 -1 -1 35 12 -1 -1 33 -1 -1

int main() {

   printf("Enter the Root Node: ");
   int n;
   scanf("%d", &n);
   if (n != -1) {
      root = (nptr)malloc(sizeof(node));
      root->data = n;
      root->left = treein();
      root->right = treein();
   } else {
      printf("No Node Present\n");
   }
   printf("\nPath to Leaf Nodes : \n");
   path(root, 0);
   printf("\n");

   return 0;
}