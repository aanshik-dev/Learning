#include <stdio.h>
int main() {
   int n, m, c = 0;
   printf("Please Enter A Number: ");
   scanf("%d", &n);
   m = n;

   while (m > 0) {
      c = c * 10 + m % 10;
      m = m / 10;
   }
   printf("The Reverse of Number %d is %d", n, c);
   return 0;
}
