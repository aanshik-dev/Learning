// Write a program in C to read n int
// values in an array and display it in
// reverse order

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
   printf("\n ");
   for (int i = s; i > 0; i--) {
      printf(" %d ", arr[i - 1]);
   }

   return 0;
}
