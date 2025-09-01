// Consider the following array : 10, 2, 3, 1, 56, 48, 24, 79, 11, 90, 35, 23, 36, 78 Write a C program to find out among Insertion sort, Selection sort, and Bubble sort algo - rithms, which one needs the minimum number of swaps ?
#include <stdio.h>

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

// 10 2 3 1 56 48 24 79 11 90 35 23 36 78
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

int main() {
   int n;
   printf("\nEnter Size of Array: ");
   scanf("%d", &n);
   int arr[n];
   printf("Enter the elements of array: ");
   for (int i = 0; i < n; i++) {
      scanf("%d", &arr[i]);
   }

   printf("\nEntered Array : ");
   for (int i = 0; i < n; i++) {
      printf(" %d", arr[i]);
   }
   printf("\n");

   int temp[n];
   for (int i = 0; i < n; i++) {
      temp[i] = arr[i];
   }
   int ins = insertSort(temp, n);
   for (int i = 0; i < n; i++) {
      temp[i] = arr[i];
   }
   int sel = selectSort(temp, n);
   int bub = bubbleSort(arr, n);

   printf("\nInsertion Sort : %d", ins);
   printf("\nSelection Sort : %d", sel);
   printf("\nBubble Sort : %d", bub);

   return 0;
}