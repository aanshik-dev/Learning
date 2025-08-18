#include <stdio.h>
int main() {
   char i = 'a';
   printf("Please Enter a Character: ");
   scanf("%c", &i);

   if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z')) {
      printf("The Entered Character %c an Alphabet.", i);
   } else if (i >= '0' && i <= '9') {
      printf("The Entered Character %c is a digit.", i);
   } else {
      printf("The Entered Character %c is a Special Character.", i);
   }
}