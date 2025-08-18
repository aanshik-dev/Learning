#include <math.h>
#include <stdio.h>

int prime(int); // Prototypes of functions written below
int reverse(int);
int binconv(int);
int decconv(int);

int main() {
   int m, n; // Takin User input
   printf("Please Enter Lower limit Number: ");
   scanf("%d", &m);
   printf("Please Enter Upper limit Number: ");
   scanf("%d", &n);

   for (int i = m; i < n; i++) {          // loop to iterate range
      if (prime(i) == 1) {                // Check for prime
         if (reverse(i) == i) {           // check for palindrome
            int bin = binconv(i);         // convert dec to binary
            int binrev = reverse(bin);    // Store reversed binary
            int revdec = decconv(binrev); // convert rev dec to binary
            if (prime(revdec) == 1)       // Check dec for Prime
               printf("%03d\n", i);       // Prints palinprime num
         }
      }
   }

   // printf("%d", reverse(12340));
   return 0;
}

int prime(int num) {
   if (num == 1)
      return 0; // checks and returns 1 for prime
   else {
      for (int i = 2; i < num; i++) {
         if (num % i == 0)
            return 0;
      }
      return 1;
   }
}

int reverse(int org) {
   int rev = 0; // reverses no.
   while (org != 0) {
      rev = rev * 10 + org % 10;
      org = org / 10;
   }
   return rev;
}

int binconv(int dec) { // converts dec to binary
   int revbin = 0, bin;
   while (dec != 0) {
      revbin = revbin * 10 + dec % 2;
      dec = dec / 2;
   }
   bin = reverse(revbin);
   return bin;
}

int decconv(int bin) { // converts binary to dec
   int dec = 0, i = 0;
   while (bin != 0) {
      dec = dec + (bin % 2) * pow(2, i);
      bin = bin / 10;
      i++;
   }
   return dec;
}
