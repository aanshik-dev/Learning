#include <stdio.h>
int main() {
   int n;
   printf("Please enter a number: ");
   scanf("%d", &n);
   if (n % 7 == 0 || n % 13 == 0)
      printf("The number %d is divisible by either 7 or 13 or both.", n);
   else
      printf("The number %d is neither divisible by 7 nor 13.", n);
   return 0;
}
