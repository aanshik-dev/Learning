#include <stdio.h>

int main() {

   int even = 0, odd = 0;
   int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   for (int i = 0; i < 10; i++) {
      if (arr[i] % 2 == 0) {
         even++;
      } else {
         odd++;
      }
   }
   printf("Total Odd Numbers: %d \nTotal Even Numbers: %d", even, odd);
   return 0;
}