#include <stdio.h>
#define IS_LOWERCASE(c) ((c) >= 'a' && (c) <= 'z')

int main() {

   char ch;
   printf("Enter a Character: ");
   scanf("%c", &ch);
   if (IS_LOWERCASE(ch)) {
      printf("%c is a lowercase letter.\n", ch);
   } else {
      printf("%c is not a lowercase letter.\n", ch);
   }
   return 0;
}