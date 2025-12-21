#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
   int data;
   struct node *left, *right;
} node, *nptr;

typedef struct qnode {
   nptr tnode;
   struct qnode *next;
} qnode, *qnptr;

qnptr front = NULL, rear = NULL;
nptr root = NULL;
int singleNode = 0;

nptr deq() {
   if (front == NULL) {
      return NULL;
   } else {
      qnptr temp = front;
      front = front->next;
      nptr temp1 = temp->tnode;
      free(temp);
      return temp1;
   }
}

void enq(nptr tnode) {
   qnptr temp = (qnptr)malloc(sizeof(qnode));
   temp->tnode = tnode;
   temp->next = NULL;
   if (front == NULL) {
      front = temp;
      rear = temp;
      return;
   }
   rear->next = temp;
   rear = temp;
}

nptr addNode(int data) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = data;
   temp->left = temp->right = NULL;
   return temp;
}

void preOrder(nptr root) {
   if (root == NULL) {
      return;
   } else {
      if ((root->left == NULL) ^ (root->right == NULL)) {
         singleNode++;
         printf("*");
      }
      printf("%d ", root->data);
      preOrder(root->left);
      preOrder(root->right);
   }
}

int main() {
   int len = 1, n;
   printf("\nPlease enter levels of tree: ");
   scanf("%d", &n);
   for (int i = 0; i < n; i++) {
      len *= 2;
   }
   len--;
   int arr[len];
   printf("\nPlease enter node of tree in level order with -1 for NULL: ");
   for (int i = 0; i < len; i++) {
      scanf("%d", &arr[i]);
   }
   // 1 2 4 3 5 6 7 -1 15 -1 8 -1 -1 9 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 10 11 -1 -1
   root = (nptr)malloc(sizeof(node));
   root->data = arr[0];
   root->left = root->right = NULL;
   enq(root);

   for (int i = 1; i < len;) {
      nptr temp1, temp2, temp3;
      temp1 = temp2 = NULL;
      temp1 = (nptr)malloc(sizeof(node));
      temp2 = (nptr)malloc(sizeof(node));
      temp1->data = arr[i++];
      temp2->data = arr[i++];
      temp1->left = temp1->right = NULL;
      temp2->left = temp2->right = NULL;
      enq(temp1);
      enq(temp2);
      temp3 = deq();
      if (temp3 == NULL || temp3->data == -1)
         continue;
      temp3->left = temp1->data == -1 ? NULL : temp1;
      temp3->right = temp2->data == -1 ? NULL : temp2;
   }

   printf("\nInput Tree in level order\n");
   for (int i = 0; i < len; i++) {
      printf("%d ", arr[i]);
   }
   printf("\n\nPreorder Traversal: ");
   preOrder(root);
   printf("\nNumber of half nodes: %d \n\n", singleNode);
   return 0;
}