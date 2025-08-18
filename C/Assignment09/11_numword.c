// Given a non-negative integer n ∈ [0, 100000000],
// write a program in C to print it in words. For instance,
// for the input integer n = 19450274, the output should be

// One Crore Ninety Four Lakh Fifty Thousand Two Hundred Seventy Four

#include <stdio.h>
#include <string.h>
int wordprt(int n, int lim);

int main() {

   int n;
   char word[][9] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
   char ten[][9] = {"Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninty", "Hundred", "Thousand", "Lakh", "Crore"};

   printf("Enter a number less than 10 Crore: ");
   scanf("%d", &n);
   int cur = 0;
   if (n <= 100000000 && n >= 0) {
      if (n / 10000000 == 0) {
         if (n / 100000 == 20) {

            if {
               cur = n / 100000000;
               printf("%s" ten[]);
            }
            printf("%s", word[n]);
         }

         else
            printf("Number is Out of Range");
         return 0;
      }
   } else {
      printf("Number is Out of Range");
      return 0;
   }
}