// Write a program in C to reverse a string.
// The string is user input. Without using string.h

#include <stdio.h>
int main() {

   int len = 0;
   char str[100];
   printf("Enter a String: ");
   scanf("%[^\n]", str);
   for (int i = 0; str[i] != '\0'; i++) {
      len++;
   }
   char c;
   for (int i = 0; i < len / 2; i++) {
      c = str[i];
      str[i] = str[len - i - 1];
      str[len - i - 1] = c;
   }
   printf("%s", str);
   return 0;
}