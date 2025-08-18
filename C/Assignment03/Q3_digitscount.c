#include <stdio.h>
int main() {
   int n, m, c = 0;
   printf("Please Enter A Number: ");
   scanf("%d", &n);
   m = n;
   while (m > 0) {
      m = m / 10;
      c++;
   }
   printf("Number of digits in %d are %d", n, c);
   return 0;
}
