// Write a program in C to copy the elements of one array into another array.

#include <stdio.h>
int main() {
   int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   int size = sizeof(arr) / sizeof(int);
   int arrcopy[size];
   printf(" Copied Array\n");
   for (int i = 0; i < size; i++) {
      arrcopy[i] = arr[i];
      printf(" %d ", arrcopy[i]);
   }
   return 0;
}
