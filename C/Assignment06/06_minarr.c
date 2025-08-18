// Write a program in C to find the
// minimum element in an array.

#include <stdio.h>
int main() {
   int s;
   printf("Please enter size of array: ");
   scanf("%d", &s);
   int arr[s];

   printf("Please enter values of array:\n\n");
   for (int i = 0; i < s; i++) {
      scanf("%d", &arr[i]);
   }
   printf("\n");
   int min = arr[0];
   for (int i = 0; i < s; i++) {
      printf(" %d ", arr[i]);
      if (min > arr[i])
         min = arr[i];
   }
   printf("\n Minimum Entry = %d \n", min);

   return 0;
}
