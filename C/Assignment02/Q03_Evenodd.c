#include <stdio.h>
int main() {
   int n;
   printf("Please Enter A number: ");
   scanf("%d", &n);
   if (n % 2 == 0) {
      printf("The given number %d is even.", n);
   } else {
      printf("The given number %d is odd.", n);
   }
   return 0;
}