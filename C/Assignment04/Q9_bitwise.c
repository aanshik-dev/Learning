#include <stdio.h>
int main() {
   int n,
       m;
   printf("Please Enter a number: ");
   scanf("%d", &n);
   printf("Please Enter another number: ");
   scanf("%d", &m);
   printf("Bit-wise And &: %d\n", n & m);
   printf("Bit-wise Or |: %d\n", n | m);
   printf("Bit-wise Ex-Or ^: %d\n", n ^ m);
   printf("Bit-wise Right Shift >>: %d, %d\n", n >> 1, m >> 1);
   printf("Bit-wise Left Shift <<: %d, %d\n", n << 1, m << 1);
   printf("Bit-wise inverse ~ : %d, %d\n", ~n, ~m);
   return 0;
}