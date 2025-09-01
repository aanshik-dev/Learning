#include <stdio.h>
#include <stdlib.h>
#define MAX 4

int arr[MAX], top = -1, end = -1;

void deq() {
   if (end == -1) {
      printf("Queue is empty\n");
   } else {
      printf("%d\n", arr[end]);
      arr[end] = 0;
      if (end == top) {
         top = -1;
         end = -2;
      }
      end = (end + 1) % MAX;
   }
}

void enq(int val) {
   if (top == -1) {
      end = 0;
      top = 0;
      // arr[top] = val;
   } else {
      top = (top + 1) % MAX;
      if (top == end) {
         printf("Queue is full, Please choose an action\n 1. Force\n 2. Skip\n");
         printf("Enter your choice: ");
         int c;
         scanf("%d", &c);
         if (c == 1) {
            printf("Value forced out: %d\n", arr[end++]);
         } else if (c == 2) {
            top = (top == 0 ? MAX - 1 : top - 1);
            return;
         }
      }
   }
   arr[top] = val;
}

int main() {

   do {
      int choice;
      printf("\n *************** MENU ***************\n [1. Enqueue] [2. Dequeue] [3. Exit]\n\n");
      printf("Please choose an option: ");
      scanf("%d", &choice);

      if (choice == 1) {
         int n;
         printf("Enter a value to Enqueue: ");
         scanf("%d", &n);
         enq(n);
      } else if (choice == 2) {
         printf("Dequeued Value: ");
         deq();
      } else if (choice == 3) {
         printf("Terminating...\n\n");
         break;
      } else {
         printf("Please enter a valid choice.\n");
      }
      printf("[ ");
      for (int i = 0; i < MAX; i++) {
         printf(" %d ", arr[i]);
      }
      printf(" ]\n");

   } while (1);
}
