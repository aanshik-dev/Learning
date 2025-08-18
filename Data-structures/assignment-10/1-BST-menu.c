#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   struct node *left, *right;
} node, *nptr;

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

void preOrder(nptr r) {
   if (r == NULL) {
      return;
   }
   printf(" %d ", r->data);
   preOrder(r->left);
   preOrder(r->right);
}

void postOrder(nptr r) {
   if (r == NULL) {
      return;
   }
   postOrder(r->left);
   postOrder(r->right);
   printf(" %d ", r->data);
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

nptr inPred(nptr r) {
   r = r->left;
   while (r->right != NULL) {
      r = r->right;
   }
   return r;
}

void deleteNode(nptr *r, int n) {
   if (*r == NULL) {
      printf("Node not found !!\n");
      return;
   }
   if (n < (*r)->data) {
      deleteNode(&(*r)->left, n);
   } else if (n > (*r)->data) {
      deleteNode(&(*r)->right, n);
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
         deleteNode(&(*r)->left, iPre->data);
      }
   }
}
//                 50
//               /    \ 
//              30    70
//             / \    / \ 
//            20 40  60 80

int main() {
   int choice;
   printf("\n   ::: MENU :::\nPlease choose from the choices below\n");
   printf("1. Insert Node\n2. Traverse\n3. Delete a node\n4. Search for a node\n5. Exit\n");
   int n, ser, del;

   do {
      printf("\nPlease enter your choice: ");
      scanf("%d", &choice);
      switch (choice) {
      case 1: // Insert Node
         printf("Please enter a value to insert : ");
         scanf("%d", &n);
         insertNode(&root, n);
         printf("Node added Successfully !!\n");
         break;
      case 2: // Traverse
         printf("1. Inorder\n2. Preorder\n3. Postorder\n");
         printf("Please enter your choice : ");
         scanf("%d", &choice);
         switch (choice) {
         case 1: // Inorder
            printf("Inorder : ");
            inOrder(root);
            printf("\n");
            break;
         case 2: // Preorder
            printf("Preorder : ");
            preOrder(root);
            printf("\n");
            break;
         case 3: // Postorder
            printf("Postorder : ");
            postOrder(root);
            printf("\n");
            break;
         default:
            printf("Please enter a valid choice !!\n");
         }
         break;
      case 3: // Delete Node
         printf("Please enter a value to delete : ");
         scanf("%d", &del);
         deleteNode(&root, del);
         break;
      case 4: // Search for a node
         printf("Please enter a Value to search : ");
         scanf("%d", &ser);
         if (searchNode(root, ser)) {
            printf("Node is Found !!\n");
         } else {
            printf("Node is Not Found !!\n");
         }
         break;
      case 5: //  Exit
         printf("Exiting the program...\n\n");
         exit(0);
         break;
      default:
         printf("Please enter a valid choice !!\n");
      }
   } while (1);
}
