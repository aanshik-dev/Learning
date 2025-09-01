#include <stdio.h>

int main() {
   // defining arrays
   int arr1[] = {2, 1, 4, 7, 5, 0, 8};
   int arr2[] = {1, 3, 4, 5, 5, 1, 3, 6, 8, 9, 0, 9};
   // getting the size of the arrays
   int n1 = sizeof(arr1) / sizeof(arr1[0]), n2 = sizeof(arr2) / sizeof(arr2[0]);
   // defining x for current index and del for deletion of duplicate elements
   int x = 0, del = 0;

   // printing the arrays
   printf("\nArray 1: ");
   for (int i = 0; i < n1; i++) {
      printf("%d ", arr1[i]);
   }
   printf("\n\n");
   printf("Initial Array 2: ");
   for (int i = 0; i < n2; i++) {
      printf("%d ", arr2[i]);
   }
   printf("\n");

   for (int i = 0; i < n1; i++) {    // iterating array 1
      for (int j = x; j < n2; j++) { // iterating array 2 from x
         if (arr1[i] == arr2[j]) {   // if same element found
            if (del == 0) {          // if first time found
               int temp = arr2[j];   // bring it ahead at x
               arr2[j] = arr2[x];
               arr2[x] = temp;
               x++;
               del = 1;
            } else {                          // if not first time found
               for (int k = j; k < n2; k++) { // delete the duplicate element
                  arr2[k] = arr2[k + 1];
               }
               n2--;
               j--;
            }
         }
      }
      del = 0; // reset del
   }

   // sorting the remaining array2 in descending order
   for (int i = x; i < n2; i++) {
      for (int j = i + 1; j < n2; j++) {
         if (arr2[i] < arr2[j]) {
            int temp = arr2[i];
            arr2[i] = arr2[j];
            arr2[j] = temp;
         }
      }
   }

   // printing the final arrays
   printf("Final Array 2: ");
   for (int i = 0; i < n2; i++) {
      printf("%d ", arr2[i]);
   }
   printf("\n\n");
   return 0;
}