// Write a program in C to check if a string is
// a palindrome or not. The string is user input.

#include <stdio.h>
#include <string.h>

int main() {

   int len = 0, isPal = 1;
   char str[100];
   printf("Enter a String: ");
   scanf("%[^\n]", str);

   len = strlen(str);
   char c;
   for (int i = 0; i <= len / 2; i++) {
      c = str[len - 1 - i];
      if (str[i] != c && str[i] != 'A' + (c - 'a') && str[i] != 'a' + (c - 'A')) {
         isPal = 0;
      }
   }
   if (isPal == 1)
      printf("The String \"%s\" is a Palindrome", str);
   else
      printf("The String \"%s\" is NOT a Palindrome", str);

   return 0;
}