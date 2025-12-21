#include <stdio.h>
int main() {
   int n;
   printf("Please enter a number: ");
   scanf("%d", &n);
   if (n % 7 == 0 && n % 13 == 0)
      printf("The number %d is divisible by both 7 and 13", n);
   else if (n % 7 != 0 && n % 13 == 0)
      printf("The number %d is divisible by 13 only", n);
   else if (n % 7 == 0 && n % 13 != 0)
      printf("The number %d is divisible by 7 only", n);
   else
      printf("The number %d is neither divisible by 7 nor 13.", n);
   return 0;
}
