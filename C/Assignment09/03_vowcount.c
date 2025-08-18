// Write a program in C to calculate the number of
// vowels in a string. The string is user input.

#include <stdio.h>
#include <string.h>

int main() {

   int vow = 0;
   char str[100];
   printf("Enter a String: ");
   scanf("%[^\n]", str);

   for (int i = 0; str[i] != '\0'; i++) {
      char c = str[i];
      if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
         vow++;
   }
   printf("There are %d vowels in \"%s\"\n", vow, str);
   return 0;
}