#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
   int data;
   struct Node *left, *right;
} node, *nptr;

node *addNode(int data) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = data;
   temp->left = temp->right = NULL;
   return temp;
}

int maxlev(nptr cur) {
   if (cur == NULL) {
      return 0;
   }
   int x, y;
   x = maxlev(cur->left);
   y = maxlev(cur->right);
   return x > y ? x + 1 : y + 1;
}

int curlev = 0;

void levsum(nptr cur, int lev, int arr[]) {
   if (cur == NULL) {
      return;
   }
   arr[curlev] += cur->data;
   curlev++;
   levsum(cur->left, lev, arr);
   levsum(cur->right, lev, arr);
   curlev--;
   return;
}

int main() {
   /*        1
            / \
           2   3
          /     \
         4       8
                / \
               6   7
                  /
                 12
   */
   nptr root = addNode(1);
   root->left = addNode(2);
   root->right = addNode(3);
   root->left->left = addNode(4);
   root->right->right = addNode(8);
   root->right->right->left = addNode(6);
   root->right->right->right = addNode(7);
   root->right->right->right->left = addNode(12);

   int lev = maxlev(root);
   int arr[lev];
   for (int i = 0; i < lev; i++) {
      arr[i] = 0;
   }
   levsum(root, lev, arr);
   int max = root->data;
   for (int i = 0; i < lev; i++) {
      max = arr[i] > max ? arr[i] : max;
   }

   printf("\nMaximum Level Sum: %d\n\n", max);
   return 0;
}
