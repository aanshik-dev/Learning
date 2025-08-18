#include <stdio.h>
int main() {
   char c;
   printf("Please enter a character: ");
   scanf("%c", &c);
   int a = c;
   printf("Char is '%c'\n", a);
   printf("ASCII is %d\n", a);
   if ((a >= 97 && a <= 122) || (a >= 65 && a <= 90)) {
      if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
         printf("The character '%c' is a vowel", c);
      } else {
         printf("The character '%c' is NOT a vowel", c);
      }
   } else
      printf("The character '%c' is NOT an English alphabet.", c);
   return 0;
}