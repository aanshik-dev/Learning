/*  Write a menu-based (use do... while loop to create the menu) program in C to perform following operations on strings.
1. Concatenate two strings using the strcat function. The strings are user inputs.
2. Compare two strings using the strcmp function. The strings are user inputs.
3. Calculate length of a string using the strlen function. The string is a user input.
4. Copy one string to another string using the strcpy function. The string is user input.
5. “exit” to terminate the program.
*/

#include <stdio.h>
#include <string.h>

int main() {

   char fun[4], str1[50], str2[50];
   printf("Function Menu to Choose\n\n");
   printf("[Type 'CAT']: To Concatenate two Strings\n[Type 'CMP']: To Compare two Strings\n");
   printf("[Type 'LEN']: To Find length of String\n[Type 'CPY']: To Copy String to other\n\n[Type 'EXIT']: To End Execution\n\n");

   do {
      printf("Select a Function: ");
      scanf("%s", fun);
      if (strcmp(fun, "CAT") == 0) {
         printf("Enter String A: ");
         scanf("%s", str1);
         printf("Enter String B: ");
         scanf("%s", str2);
         strcat(str1, str2);
         printf("\nConcatenated String\n");
         printf("%s\n\n", str1);
      } else if (strcmp(fun, "CMP") == 0) {
         printf("Enter String A: ");
         scanf("%s", str1);
         printf("Enter String B: ");
         scanf("%s", str2);
         if (strcmp(str1, str2) == 0)
            printf("\nStrings are Same\n\n");
         else
            printf("\nStrings are Different\n\n");
      } else if (strcmp(fun, "LEN") == 0) {
         printf("Enter a String: ");
         scanf("%s", str1);
         printf("\nLength of String is %d\n\n", strlen(str1));
      } else if (strcmp(fun, "CPY") == 0) {
         printf("Enter String to Copy: ");
         scanf("%s", str1);
         strcpy(str2, str1);
         printf("\nCopied String\n%s\n\n", str2);
      } else if (strcmp(fun, "EXIT") != 0)
         printf("\nERROR: Invalid Input\n\n");
   } while (strcmp(fun, "EXIT") != 0);
   printf("\nTerminating Execution...\n\n");
   return 0;
}
