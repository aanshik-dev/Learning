#include <stdio.h>
#include <stdlib.h>
#define MX_SIZE 50

int heap[MX_SIZE];
int size = 0;

int swap(int a, int b) {
   if (a == b)
      return;
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

void insertNode(int key) {
   if (size == MX_SIZE) {
      printf("Sorry !! The value could not be inserted due to heap overflow.\n");
      return;
   } else {
      heap[size] = key;
      if (size != 0) {
         heapUp();
      }
      size++;
      printf("Node added succesfully !!\n");
   }
}

int getMin() {
   if (size == 0) {
      return -1;
   } else {
      return heap[0];
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

void delNode() {
   if (size == 0) {
      printf("Heap is Empty !! Try inserting some values !!\n");
      return;
   } else {
      int temp = heap[0];
      heap[0] = heap[--size];
      heapDown();
      printf("Node %d deleted successfully !!\n", temp);
   }
}

int main() {
   printf("\n   ::: MENU :::   \n");
   printf("1. Insert\n");
   printf("2. Get Minimum\n");
   printf("3. Extract Minimum\n");
   printf("4. Exit\n");
   int choice;
   int key;
   do {
      printf("\nPlease enter your Choice: ");
      scanf("%d", &choice);

      if (choice == 1) {
         printf("Enter the key to insert: ");
         scanf("%d", &key);
         insertNode(key);
      } else if (choice == 2) {
         key = getMin();
         key != -1 ? printf("The smallest element is %d \n", key) : printf("Heap is Empty !! Try inserting some values !!\n");
      } else if (choice == 3) {
         delNode();
      } else if (choice == 4) {
         printf("Exiting...\n");
         break;
      } else {
         printf("Invalid choice. Please try again.\n");
      }
      printf("Current Heap: ");
      for (int i = 0; i < size; i++) {
         printf(" %d ", heap[i]);
      }
      printf("\n");
   } while (1);

   return 0;
}
