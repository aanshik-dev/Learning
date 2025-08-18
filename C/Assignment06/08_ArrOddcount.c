// Write a program in C to count the occurrences of odd numbers in an array.

#include <stdio.h>
int main() {
   int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   int size = sizeof(arr) / sizeof(int);
   int odd = 0;
   for (int i = 0; i < size; i++) {
      printf(" %d ", arr[i]);
      if (arr[i] % 2 == 1)
         odd++;
   }
   printf("\n Number of Odd Entries = %d ", odd);
   return 0;
}
