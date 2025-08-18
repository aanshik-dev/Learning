#include <stdio.h>
int gcd(int, int);
int gcd(int n1, int n2) {
   if (n1 == n2)
      return n1;
   else if (n1 > n2)
      return gcd(n1 - n2, n2);
   else if (n1 < n2)
      return gcd(n2 - n1, n1);
}

int main() {
   int n1, n2;
   printf("Enter First Number: ");
   scanf("%d", &n1);
   printf("Enter Second Number: ");
   scanf("%d", &n2);
   printf("GCD of %d and %d is %d", n1, n2, gcd(n1, n2));
   return 0;
}
