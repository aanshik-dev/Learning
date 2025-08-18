// Write a program in C to count the number of words in a function.

#include <stdio.h>
int main() {

   int wrd = 0;
   char str[100];
   printf("Enter a String: ");
   scanf("%[^\n]", str);
   for (int i = 1; str[i - 1] != '\0'; i++) {
      if ((str[i] == ' ' || str[i] == '\0') && str[i - 1] != ' ')
         wrd++;
   }
   printf("Total words in \"%s\" are %d", str, wrd);
   return 0;
}