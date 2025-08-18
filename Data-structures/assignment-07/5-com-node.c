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

int isNode(nptr r, int n) {
   if (r == NULL) {
      return 0;
   } else if (r->data == n) {
      return 1;
   } else if (r->data > n) {
      return isNode(r->left, n);
   } else {
      return isNode(r->right, n);
   }
}

void comNode(nptr r, int n1, int n2) {
   if (r == NULL) {
      return;
   } else {
      int n = r->data;
      if (root->data == n1 || root->data == n2) {
         printf("No Common Ancestor Node !!\n\n");
      } else if (n > n1 && n < n2 || n > n2 && n < n1) {
         printf("Lowest Common Ancestor Node: %d\n\n", n);
         return;
      } else if (n > n1 && n > n2) {
         comNode(r->left, n1, n2);
      } else if (n < n1 && n < n2) {
         comNode(r->right, n1, n2);
      }
   }
   return;
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
   // 15 7 19 3 -1 16 21 -1 5 -1 -1 -1 18 -1 -1
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
   int n1, n2;
   printf("Please enter first node: ");
   scanf("%d", &n1);
   printf("Please enter second node: ");
   scanf("%d", &n2);

   printf("\nInput Tree in level order\n");
   for (int i = 0; i < len; i++) {
      printf("%d ", arr[i]);
   }
   printf("\n\n");
   (isNode(root, n1) && isNode(root, n2)) ? comNode(root, n1, n2) : printf("Not valid pair of nodes !!\n");

   return 0;
}