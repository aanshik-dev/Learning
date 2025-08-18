// Write a program in C to find a pair of
// elements in an array of int, such that,
// the sum of these elements is equal to
// a given number.

#include <stdio.h>

int main() {
   int n, k;
   printf("\nPlease enter size of array: ");
   scanf("%d", &n);
   int arr[n];
   printf("Please enter an array of size %d: ", n);
   for (int i = 0; i < n; i++) {
      scanf(" %d", &arr[i]);
   }

   printf("\nPlease enter a number to find sum: ");
   scanf("%d", &k);
   printf("\nArray: ");
   for (int i = 0; i < n; i++) {
      printf(" %2d ", arr[i]);
   }
   printf("\n\n");
   int flag = 0;
   for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
         int sum = arr[i] + arr[j];
         if (sum == k) {
            printf("The Pair is  %d  %d\n", arr[i], arr[j]);
            flag++;
            break;
         }
      }
   }
   if (flag == 0)
      printf("Sorry No pair in array!!\n\n");
   else
      printf("\n\n");
   return 0;
}
