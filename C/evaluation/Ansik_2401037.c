// Write c function which will print the intersection of two arrays.
// The result should contain all elements which are common in both array.

#include <stdio.h>
int main() {
   int arr1[6]; // declaration of arrays
   int arr2[4];

   printf("Please Enter an array\n");
   for (int i = 0; i < 6; i++) { // iteration to take array1 input
      scanf("%d", &arr1[i]);
   }
   printf("Please Enter another array\n");
   for (int i = 0; i < 4; i++) { // iteration to take array2 input
      scanf("%d", &arr2[i]);
   }
   printf("\nThe Common elements in both arrays are: ");

   for (int i = 0; i < 6; i++) { // search and print common elements
      for (int j = 0; j < 4; j++) {
         if (arr1[i] == arr2[j]) {
            printf(" %d ", arr1[i]);
            break; // break inner loop if found common
         }
      }
   }
   return 0;
}
