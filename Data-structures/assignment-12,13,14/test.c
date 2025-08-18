#include <stdio.h>
#include <stdlib.h>
struct node {
   struct node *left, *right;
   int data, height;
};
struct node *newnode(int n) { // NEWNODE CREATE
   struct node *root = (struct node *)malloc(sizeof(struct node));
   root->data = n;
   root->left = NULL;
   root->right = NULL;
   root->height = 1;
   return root;
}
void update_height(struct node *root) { // UPDATE HEIGHT
   if (root == NULL) {
      return;
   }
   int x = root->left ? root->left->height : 0;
   int y = root->right ? root->right->height : 0;
   root->height = (x > y ? x : y) + 1;
}
int bal_fac(struct node *root) { // BALANCE FACTOR
   if (root == NULL) {
      return 0;
   }
   int x = root->left ? root->left->height : 0;
   int y = root->right ? root->right->height : 0;
   return x - y;
}
struct node *Right_rotate(struct node *root) { // RIGHT ROTATE FUNCTION
   struct node *temp = root;
   root = root->left;
   temp->left = root->right;
   root->right = temp;
   update_height(temp);
   update_height(root);
   return root;
}
struct node *Left_rotate(struct node *root) { // LEFT ROTATE FUNCTION
   struct node *temp = root;
   root = root->right;
   temp->right = root->left;
   root->left = temp;
   update_height(temp);
   update_height(root);
   return root;
}
struct node *creat(struct node *root, int n) { // CREATE AVL TREE
   if (root == NULL) {
      return newnode(n);
   }
   if (root->data > n)
      root->left = creat(root->left, n);
   else if (root->data < n)
      root->right = creat(root->right, n);

   update_height(root);
   int BF = bal_fac(root);

   if (BF > 1) {
      int bf_l = bal_fac(root->left);
      if (bf_l >= 0) {
         root = Right_rotate(root);
      } else {
         root->left = Left_rotate(root->left);
         root = Right_rotate(root);
      }
   }
   if (BF < -1) {
      int bf_r = bal_fac(root->right);
      if (bf_r <= 0) {
         root = Left_rotate(root);
      } else {
         root->right = Right_rotate(root->right);
         root = Left_rotate(root);
      }
   }
   return root;
}

struct node *delet(struct node *root, int n) { // delete function
   if (root == NULL) {
      return NULL;
   }

   if (root->data > n)
      root->left = delet(root->left, n);
   else if (root->data < n)
      root->right = delet(root->right, n);
   else {
      if (root->left == NULL && root->right == NULL) {
         free(root);
         return NULL;
      } else if (root->left == NULL || root->right == NULL) {
         struct node *temp = (root->left == NULL ? root->right : root->left);
         free(root);
         return temp;
      } else {
         struct node *temp = root->left;
         while (temp->right != NULL) {
            temp = temp->right;
         }
         root->data = temp->data;
         root->left = delet(root->left, temp->data);
      }
   }

   update_height(root);
   int BF = bal_fac(root);
   if (BF > 1) {
      int bf = bal_fac(root->left);
      if (bf >= 0) {
         root = Right_rotate(root);
      } else {
         root->left = Left_rotate(root->left);
         root = Right_rotate(root);
      }
   } else if (BF < -1) {
      int bf = bal_fac(root->right);
      if (bf <= 0) {
         root = Left_rotate(root);
      } else {
         root->right = Right_rotate(root->right);
         root = Left_rotate(root);
      }
   }
   return root;
}

void inorder(struct node *root) { // INORDER FUNCTION
   if (root == NULL) {
      return;
   }
   inorder(root->left);
   printf("%d\t", root->data);
   inorder(root->right);
}
void preorder(struct node *root) { // INORDER FUNCTION
   if (root == NULL) {
      return;
   }
   printf("%d\t", root->data);
   preorder(root->left);
   preorder(root->right);
}

int main() { // MAIN FUNCTION
   struct node *root = NULL;
   int n, m;
   printf("enter number of nodes:");
   scanf("%d", &n);
   printf("enter node one by one:");
   for (int i = 0; i < n; i++) {
      scanf("%d", &m);
      root = creat(root, m);
   }
   inorder(root);
   printf("\n");
   root = delet(root, 90);
   inorder(root);
   printf("\n");
   preorder(root);
}