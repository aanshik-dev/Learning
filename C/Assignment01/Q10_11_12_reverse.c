#include <stdio.h>
int main() {
   int a, b, c, d, e, rev;
   printf("Please Enter A Number: ");
   scanf("%d", &a);
   b = a % 100;       // 34
   c = (a - b) / 100; // 6
   d = b % 10;        // 4
   e = (b - d) / 10;  // 3
   rev = d * 100 + e * 10 + c;
   printf("The individual Number are:\n%d\n%d\n%d\n", c, e, d);
   printf("The Sum of Digits is: %d\n", c + d + e);
   printf("The Reversed Number is: %d", rev);
   return 0;
}
