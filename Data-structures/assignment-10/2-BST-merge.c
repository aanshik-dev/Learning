#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   struct node *left, *right;
} node, *nptr;

nptr root1 = NULL;
nptr root2 = NULL;
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

void inOrder(nptr r) {
   if (r == NULL) {
      return;
   }
   inOrder(r->left);
   printf(" %d ", r->data);
   inOrder(r->right);
}

// inOrder : 20 30 40 50 60 70 80
//                 50
//               /    \ 
//              30    70
//             / \    / \ 
//            20 40  60 80

//   inOrder : 3 5 7 10 12 15 18 20 30 40 50 60 70 80
//                 50                    18
//               /    \               /      \ 
//              30    70            7          50
//             / \    / \         /  \       /   \ 
//            20 40  60 80       3   12     30   70
//           /  \                \   / \   / \   / \ 
//          10                   5  10 15 20 40 60 80
//        /   \ 
//       5     15
//      / \   /  \ 
//     3  7  12  18

//   inOrder : 3 5 7 10 12 15 18
//         10
//       /    \ 
//      5     15
//     / \    / \   
//    3   7  12 18

void merge(nptr r2) {
   if (r2 != NULL) {
      merge(r2->left);
      insertNode(&root1, r2->data);
      merge(r2->right);
   }
}

void dump(nptr r, int bst[]) {
   static int i = 0;
   if (r != NULL) {
      dump(r->left, bst);
      bst[i++] = r->data;
      dump(r->right, bst);
   }
}

// 3 5 7 10 12 15 18 20 30 40 50 60 70 80
void intoBST(nptr *r, int bst[], int st, int end) {
   if (st > end) {
      return;
   }
   int mid = (st + end) / 2;
   insertNode(&(*r), bst[mid]);
   intoBST(&(*r), bst, st, mid - 1);
   intoBST(&(*r), bst, mid + 1, end);
}

void freeTree(nptr r) {
   if (r != NULL) {
      freeTree(r->left);
      freeTree(r->right);
      free(r);
   }
}

int main() {
   int bst1[] = {50, 30, 70, 20, 40, 60, 80};
   int n = sizeof(bst1) / sizeof(bst1[0]);
   for (int i = 0; i < n; i++) {
      insertNode(&root1, bst1[i]);
   }

   int bst2[] = {10, 5, 15, 3, 7, 12, 18};
   n = sizeof(bst2) / sizeof(bst2[0]);
   for (int i = 0; i < n; i++) {
      insertNode(&root2, bst2[i]);
   }

   printf("\nInOrder of BST1 : ");
   inOrder(root1);
   printf("\nInOrder of BST2 : ");
   inOrder(root2);

   merge(root2);
   n += sizeof(bst1) / sizeof(bst1[0]);
   int bst[n];
   dump(root1, bst);
   intoBST(&root, bst, 0, n - 1);

   printf("\n\nInOrder of Merged BST : ");
   inOrder(root);
   printf("\n\n");

   free(root1);
   free(root2);
   free(root);

   return 0;
}