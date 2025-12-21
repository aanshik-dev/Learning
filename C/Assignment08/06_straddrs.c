// Write a program in C to print the address of each
// character in a given string.The string is user input.

#include <stdio.h>

int main() {
   char str[50], i = 0;
   printf("Enter a String: ");
   scanf("%s", str);
   printf("\n%s\n", str);
   printf("\nAddress of each Character\n");
   while (str[i] != '\0') {
      printf("%d) %c is at address %u\n", i + 1, str[i], &str[i]);
      i++;
   }

   return 0;
}
