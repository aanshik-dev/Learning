// Write a function in C to find the
// sum of all array elements.
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

   printf("\n  ");
   int sum = 0;
   for (int i = 0; i < s; i++) {
      printf(" %d ", arr[i]);
      sum = sum + arr[i];
   }
   printf("\n   Sum = %d \n", sum);

   return 0;
}
