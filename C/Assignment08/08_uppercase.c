//  Write a program in C to convert all lowercase characters
// to uppercase in a string. The string is user input.
#include <stdio.h>
#include <string.h>

int main() {

   char str[50];
   printf("Enter a String: ");
   scanf("%s", str);

   for (int i = 0; str[i] != '\0'; i++) {
      if (str[i] <= 'z' && str[i] >= 'a') {
         str[i] = 'A' + (str[i] - 'a');
      }
   }
   printf("\nUppercase String: %s\n", str);

   return 0;
}
