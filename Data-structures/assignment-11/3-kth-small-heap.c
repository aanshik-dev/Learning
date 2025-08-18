#include <stdio.h>
#include <stdlib.h>
#define MX_SIZE 50

int heap[MX_SIZE];
int size = 0;

int swap(int a, int b) {
   heap[a] = heap[a] ^ heap[b];
   heap[b] = heap[a] ^ heap[b];
   heap[a] = heap[a] ^ heap[b];
}

void heapUp() {
   int i = size, parent = (i - 1) / 2;
   while (heap[parent] > heap[i]) {
      swap(parent, i);
      i = parent;
      parent = (i - 1) / 2;
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

void insertNode(int key) {
   if (size == MX_SIZE) {
      return;
   } else {
      heap[size] = key;
      if (size != 0) {
         heapUp();
      }
      size++;
   }
}

void delNode() {
   if (size == 0) {
      return;
   } else {
      int temp = heap[0];
      heap[0] = heap[--size];
      heapDown();
   }
}

int getMin() {
   if (size == 0) {
      return -1;
   } else {
      return heap[0];
   }
}

int kthSmall(int k, int s) {
   if (k <= 0 || k > s) {
      printf("Please enter a valid position !! Max Position is %d\n\n", s);
      return -1;
   }
   int arr[s];
   for (int i = 0; i < s; i++) {
      arr[i] = heap[i];
   }
   for (int i = 0; i < k - 1; i++) {
      delNode();
   }
   int ret = getMin();
   for (int i = 0; i < s; i++) {
      heap[i] = arr[i];
   }
   return ret;
}

int main() {
   int input[] = {2, 6, 9, 12, 3, 8, 25, 16, 28};
   int size = sizeof(input) / sizeof(input[0]), k;
   for (int i = 0; i < size; i++) {
      insertNode(input[i]);
   }
   printf("\nPlease enter the Kth Position to find the Smallest Element: ");
   scanf("%d", &k);

   printf("Input Heap: ");
   for (int i = 0; i < size; i++) {
      printf(" %d ", heap[i]);
   }
   printf("\n");

   int val = kthSmall(k, size);
   val != -1 ? printf("The smallest element at position %d is %d \n\n", k, val) : 1;
   return 0;
}
