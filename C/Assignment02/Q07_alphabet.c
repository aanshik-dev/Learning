#include <stdio.h>
int main() {
   char c;
   printf("Please enter a character: ");
   scanf("%c", &c);
   int a = c;
   printf("Char is '%c'\n", a);
   printf("ASCII is %d\n", a);
   if (a >= 97 && a <= 122)
      printf("The character '%c' is a lowercase English alphabet.", c);
   else if (a >= 65 && a <= 90)
      printf("The character '%c' is an Uppercase English alphabet.", c);
   else
      printf("The character '%c' is not an English alphabet.", c);
   return 0;
}
