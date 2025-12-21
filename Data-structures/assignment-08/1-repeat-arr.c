// Write a C program to find the repeating elements in an unsorted array. For example : If the array is 4, 2, 4, 5, 2, 3, 1 with size = 7 with all elements occurring once except 2 and 4 which occur twice.So the output should be 4 2

#include <stdio.h>
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

   printf("\nRepeated elements : ");
   for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
         if (arr[i] == arr[j]) {
            printf(" %d", arr[i]);
            for (int k = j; k < n - 1; k++) {
               arr[k] = arr[k + 1];
            }
            n--;
         }
      }
   }
   
   printf("\n\n");
   return 0;
}