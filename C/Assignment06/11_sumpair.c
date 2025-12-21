// Write a program in C to find a pair of
// elements in an array of int, such that,
// the sum of these elements is equal to
// a given number.

#include <stdio.h>

int main() {
   int n;
   printf("Please enter a number: ");
   scanf("%d", &n);
   printf("\nArray: ");
   int arr[] = {9, 8, 7, 5, 3, 1, 2, 4};
   int size = sizeof(arr) / sizeof(int);
   for (int i = 0; i < size; i++) {
      printf(" %2d ", arr[i]);
   }
   printf("\n\n");
   int flag = 0;
   for (int i = 0; i < size; i++) {
      for (int j = i + 1; j < size; j++) {
         int sum = arr[i] + arr[j];
         if (sum == n) {
            printf("The Pair is  %d  %d\n", arr[i], arr[j]);
            flag++;
            break;
         }
      }
   }
   if (flag == 0)
      printf("\nSorry No pair in array!!\n");
   return 0;
}
