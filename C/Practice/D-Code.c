#include <stdio.h>

int main() {
   int m = 0, n = 0, p = 1, s = 0, m1 = 0, x = 0, i = 0, add;
   printf("Please enter a number m: ");
   scanf("%d", &m);
   printf("Please enter a number n: ");
   scanf("%d", &n);

   if (m <= 0 || n <= 0 || m > 100000 || n > 100000) {
      printf("Error: Please enter Positive numbers which are less than 100,000");
   } else if (m <= n) {
      for (int a = m; a <= n; a++) { // loop for every next number of m
         m1 = a;                     // saves a for further use
         while (m1 != 0) {           // gives product p of digits
            p = p * (m1 % 10);
            m1 = m1 / 10;
         }

         m1 = a;           // saves a for further use
         while (m1 != 0) { // gives sum s of digits
            s = s + (m1 % 10);
            m1 = m1 / 10;
         }

         x = p + s; // gives SUM x of product and sum
         add = x;   // saves x for further use

         while (x != 0) { // invert the digits of number
            i = i * 10 + (x % 10);
            x = x / 10;
         }

         if (i == add) { // check for palindrome.
            printf("Qual. No. %d, palindrome: %d \n", a, add);
         }
         p = 1; // resets value for next loop
         s = 0;
         i = 0;
         x = 0;
      }
   } else {
      printf("m should be less than n.");
   }
}