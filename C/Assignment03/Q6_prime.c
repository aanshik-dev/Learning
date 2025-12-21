#include <stdio.h>
int main() {
   int n, s = 0, i;
   printf("Please Enter a number N: ");
   scanf("%d", &n);

   for (i = 2; i < n; i++) {
      if (n % i == 0) {
         s = 1;
         break;
      }
   }

   if (s == 0) {
      printf("The Entered Number %d is Prime.", n);
   } else if (s == 1) {
      printf("The Entered Number %d is Not Prime.", n);
   }
   return 0;
}