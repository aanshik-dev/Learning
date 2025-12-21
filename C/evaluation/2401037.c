#include <math.h>
#include <stdio.h>

int binconv(int dec) {
   int d, b = 0, bin;
   d = dec;
   while (d != 0) {
      b = b * 10 + d % 2;
      d = d / 2;
   }
   bin = b;
   b = 0;
   return bin;
}

int decconv(int bin) {
   int d = 0, b, i = 0, dec;
   b = bin;
   while (b != 0) {
      d = d + (b % 2) * pow(2, i);
      b = b / 10;
      i++;
   }
   dec = d;
   d = 0;
   return dec;
}

int main() {

   int m, n, rev = 0, rev2 = 0;
   printf("Please Enter Lower limit Number: ");
   scanf("%d", &m);
   printf("Please Enter Upper limit Number: ");
   scanf("%d", &n);

   for (int i = m; i < n; i++) {
      int s = 0, s2 = 0;
      for (int j = 2; j < i; j++) { // checks for prime
         if (i % j == 0) {
            s = 1;
            break;
         }
      }
      if (s == 0) {
         int org = i; // reverses no.
         while (org != 0) {
            rev = rev * 10 + org % 10;
            org = org / 10;
         }

         if (i == rev) { // checks for palindrome
            int bin = binconv(i);
            int org2 = bin;

            while (org2 != 0) {
               rev2 = rev2 * 10 + org2 % 10;
               org2 = org2 / 10;

               int dec = decconv(rev2);

               for (int j = 2; j < dec; j++) {

                  if (i % j == 0) {
                     s2 = 1;
                     break;
                  }
               }
               if (s2 == 1) {
                  printf("%d\n", i);
               }
            }
         }
         rev = 0;
      }
      s == 0;
   }

   return 0;
}

// for(i=1;i<n;i++){}
