#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   struct node *left, *right;
   int height;
} node, *nptr;

nptr root = NULL;
int height(nptr r) {
   if (r == NULL) {
      return 0;
   }
   return r->height;
}

int max(nptr n1, nptr n2) {
   int a = height(n1);
   int b = height(n2);
   return a > b ? a : b;
}

nptr inPre(nptr r) {
   nptr temp = r->left;
   while (temp->right != NULL) {
      temp = temp->right;
   }
   return temp;
}

int balFactor(nptr r) {
   if (r == NULL) {
      return 0;
   }
   return height(r->left) - height(r->right);
}

void lRot(nptr *node) {
   nptr subtree = (*node)->right;
   nptr temp = subtree->left;

   subtree->left = (*node);
   *node = subtree;
   (*node)->left->right = temp;

   (*node)->left->height = max((*node)->left->left, (*node)->left->right) + 1;
   (*node)->height = max((*node)->left, (*node)->right) + 1;
}
void rRot(nptr *node) {
   nptr subtree = (*node)->left;
   nptr temp = subtree->right;

   subtree->right = (*node);
   *node = subtree;
   (*node)->right->left = temp;

   (*node)->right->height = max((*node)->right->left, (*node)->right->right) + 1;
   (*node)->height = max((*node)->left, (*node)->right) + 1;
}

void avlDelete(nptr *r, int val) {
   if (!(*r)) {
      return;
   } else if (val < (*r)->data) {
      avlDelete(&(*r)->left, val);
   } else if (val > (*r)->data) {
      avlDelete(&(*r)->right, val);
   } else {
      if ((*r)->left == NULL) {
         nptr temp = (*r);
         (*r) = (*r)->right;
         free(temp);
         printf("Deleted\n");
         return;
      } else if ((*r)->right == NULL) {
         nptr temp = (*r);
         (*r) = (*r)->left;
         free(temp);
         printf("Deleted\n");
         return;
      } else {
         nptr temp = inPre(*r);
         (*r)->data = temp->data;
         avlDelete(&(*r)->left, temp->data);
      }
   }
   (*r)->height = max((*r)->left, (*r)->right) + 1;
   int bf = balFactor(*r);

   if (bf > 1) {
      if (balFactor((*r)->left) >= 0) {
         rRot(r);
      } else {
         lRot(&(*r)->left);
         rRot(r);
      }
   } else if (bf < -1) {
      if (balFactor((*r)->right) <= 0) {
         lRot(r);
      } else {
         rRot(&(*r)->right);
         lRot(r);
      }
   }
}

void avlIn(nptr *r, int val) {
   if (*r == NULL) {
      nptr temp = (nptr)malloc(sizeof(node));
      temp->data = val;
      temp->height = 1;
      temp->left = NULL;
      temp->right = NULL;
      *r = temp;
      return;
   } else if (val < (*r)->data) {
      avlIn(&(*r)->left, val);
   } else if (val > (*r)->data) {
      avlIn(&(*r)->right, val);
   }

   (*r)->height = max((*r)->left, (*r)->right) + 1;
   int bf = balFactor(*r);

   if (bf > 1) {
      if (balFactor((*r)->left) >= 0) {
         rRot(r);
      } else {
         lRot(&(*r)->left);
         rRot(r);
      }
   } else if (bf < -1) {
      if (balFactor((*r)->right) <= 0) {
         lRot(r);
      } else {
         rRot(&(*r)->right);
         lRot(r);
      }
   }
}

void prtRange(nptr root, int min, int max) {
   if (root == NULL)
      return;
   if (min < root->data)
      prtRange(root->left, min, max);
   if (min <= root->data && root->data <= max)
      printf("%d ", root->data);
   if (max > root->data)
      prtRange(root->right, min, max);
}

// 50 20 60 10 40 70 5 15 30 45 65 80 25
int arr[50];
int size;

void swap(int i, int j) {
   int temp = arr[i];
   arr[i] = arr[j];
   arr[j] = temp;
}

void heapup() {
   int k = size;
   int parent = (k - 1) / 2;
   while (arr[parent] > arr[k] && parent >= 0) {
      swap(parent, k);
      k = parent;
      parent = (k - 1) / 2;
   }
}

void heapIn(int key) {
   if (size == 50) {
      printf("full\n");
      return;
   } else {
      arr[size] = key;
      if (size != 0) {
         heapup();
      }
      size++;
   }
}

void heapDown() {
   int i = 0, left, right, min = i;
   while (1) {
      left = 2 * i + 1;
      right = 2 * i + 2;
      if (left <= size && heap[left] < heap[min]) {
         min = left;
      }
      if (right <= size && heap[right] < heap[min]) {
         min = right;
      }
      if (min != i) {
         swap(i, min);
         i = min;
      } else {
         break;
      }
   }
}

int heapout() {
   if (size == 0) {
      printf("heap is empty\n");
      return;
   } else {
      int temp = arr[0];
      arr[0] = arr[--size];
      heapdown();
      return temp;
   }
}

void enq(int val) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = val;
   if (end == NULL) {
      end = temp;
      top = temp;
   }
   temp->next = end;
   top->next = temp;
   top = temp;
}

void deq() {
   if (end == NULL) {
      printf("Queue is Empty !!\n");
      return;
   } else if (end == top) {
      printf("Dequeued Value: %d\n", end->data);
      free(end);
      end = NULL;
      top = NULL;
      return;
   } else {
      top->next = end->next;
      printf("Dequeued Value: %d\n", end->data);
      free(end);
      end = top->next;
   }
}

nptr addNode(nptr head, int data) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = data;
   temp->next = NULL;
   if (head == NULL) {
      return temp;
   }

   nptr h = head;
   while (h->next != NULL) {
      h = h->next;
   }
   h->next = temp;
   return head;
}

nptr delNode(nptr head, int post) {
   if (!head) {
      printf("Sorry, the list is empty\n");
      return head;
   }
   nptr temp = head;
   if (post == 1) {
      head = temp->next;
      free(temp);
      return head;
   }
   for (int i = 1; i < post - 1; i++) {
      if (temp->next->next == NULL) {
         printf("This location is invalid\n");
         return head;
      }
      temp = temp->next;
   }
   nptr del = temp->next;
   temp->next = temp->next->next;
   free(del);
   return head;
}

void addNode(int val) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = val;
   temp->next = temp;
   temp->prev = temp;
   if (head) {
      temp->prev = head->prev;
      temp->next = head;
      head->prev->next = temp;
      head->prev = temp;
   }
   head = temp;
}

void push(nptr *top, int val) {
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = val;
   temp->prev = *top;
   *top = temp;
}

int pop(nptr *top) {
   if (*top != NULL) {
      nptr temp = *top;
      int ret = (*top)->data;
      *top = (*top)->prev;
      free(temp);
      return ret;
   } else
      return -1;
}

void dupstack(nptr top, nptr *topC) {
   if (top->prev == NULL) {
      push(topC, top->data);
      return;
   } else {
      dupstack(top->prev, topC);
      push(topC, top->data);
   }
}


void Conv(char str[], char out[], int flag) {
   int j = 0;
   for (int i = 0; str[i] != '\0'; i++) {
      char c = str[i];
      if (c >= 'A' && c <= 'Z') {
         out[j++] = c;
      } else if (c == '(') {
         push(c);
      } else if (c == ')') {
         while (top->data != '(') {
            out[j++] = top->data;
            pop();
         }
         pop();
      } else if (c == '+' || c == '-' || c == '*' || c == '/') {

         while (flag == 1 ? pref(c) <= (top != NULL ? pref(top->data) : 0) : pref(c) < (top != NULL ? pref(top->data) : 0)) {
            out[j++] = top->data;
            pop();
         }
         push(c);
      }
   }

   while (top != NULL) {
      out[j++] = top->data;
      pop();
   }
}

nptr treein() {
   int n;
   scanf("%d", &n);
   if (n == -1)
      return NULL;
   nptr temp = (nptr)malloc(sizeof(node));
   temp->data = n;
   printf("Enter Left Child of %d: ", n);
   temp->left = treein();
   printf("Enter Right Child of %d: ", n);
   temp->right = treein();
   return temp;
}


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

void merge(int arr[], int l, int m, int r) {
   int i, j, k;
   int n1 = m - l + 1;
   int n2 = r - m;
   int L[n1], R[n2];
   for (i = 0; i < n1; i++)
      L[i] = arr[l + i];
   for (j = 0; j < n2; j++)
      R[j] = arr[m + 1 + j];
   i = 0;
   j = 0;
   k = l;
   while (i < n1 && j < n2) {
      if (L[i] <= R[j]) {
         arr[k] = L[i];
         i++;
      } else {
         arr[k] = R[j];
         j++;
      }
      k++;
   }
   while (i < n1) {
      arr[k] = L[i];
      i++;
      k++;
   }
   while (j < n2) {
      arr[k] = R[j];
      j++;
      k++;
   }
}

void mergeSort(int arr[], int l, int r) {
   if (l < r) {
      int m = l + (r - l) / 2;
      mergeSort(arr, l, m);
      mergeSort(arr, m + 1, r);
      merge(arr, l, m, r);
   }
}

void quickSort(int arr[], int l, int r) {
   if (l >= r)
      return;
   int pivot = arr[l];
   int i = l + 1, j = r;
   while (i <= j) {
      while (i <= r && arr[i] < pivot)
         i++;
      while (j >= l && arr[j] > pivot)
         j--;
      if (i < j) {
         arr[i] ^= arr[j];
         arr[j] ^= arr[i];
         arr[i] ^= arr[j];
         i++;
         j--;
      }
   }
   if (j > l) {
      arr[l] ^= arr[j];
      arr[j] ^= arr[l];
      arr[l] ^= arr[j];
   }
   quickSort(arr, l, j - 1);
   quickSort(arr, j + 1, r);
}

int insertSort(int arr[], int size) {
   int ins = 0;
   for (int i = 1; i < size; i++) {
      int key = arr[i];
      int j = i - 1;
      while (arr[j] > key && j >= 0) {
         arr[j + 1] = arr[j];
         j--;
         ins++;
      }
      arr[j + 1] = key;
   }
   return ins;
}

int selectSort(int arr[], int n) {
   int sel = 0;
   for (int i = 0; i < n; i++) {
      int min = i;
      for (int j = i + 1; j < n; j++) {
         if (arr[j] < arr[min])
            min = j;
      }
      if (min == i)
         continue;
      arr[i] = arr[i] ^ arr[min];
      arr[min] = arr[i] ^ arr[min];
      arr[i] = arr[i] ^ arr[min];
      sel++;
   }
   return sel;
}

int bubbleSort(int arr[], int n) {
   int swap = 0;
   for (int i = 0; i < n - 1; i++) {
      // int flag = 0;
      for (int j = 0; j < n - i - 1; j++) {
         if (arr[j + 1] < arr[j]) {
            arr[j + 1] = arr[j + 1] ^ arr[j];
            arr[j] = arr[j + 1] ^ arr[j];
            arr[j + 1] = arr[j + 1] ^ arr[j];
            swap++;
         }
      }
   }
   return swap;
}





int main() {
   heapIn(25);
}
