// Write a program in C to search the location
// (index) of given word in a sentence.

#include <stdio.h>
#include <string.h>

int main() {

   int slen, flag;
   char str[100], wrd[30];
   printf("Enter a String: ");
   scanf(" %98[^\n]", str);
   printf("Enter a String: ");
   scanf(" %28[^\n]", wrd);

   slen = strlen(wrd);
   wrd[slen] = ' ';
   wrd[slen + 1] = '\0';
   slen = strlen(str);
   str[slen] = ' ';
   str[slen + 1] = '\0';
   slen = strlen(wrd);

   for (int i = 0; str[i] != '\0'; i++) {
      flag = 1;
      for (int j = 0; j < slen; j++) {
         if (wrd[j] != str[i + j]) {
            flag = 0;
            break;
         }
      }
      if (flag == 1) {
         wrd[slen - 1] = wrd[slen];
         printf("\nWord \"%s\" is present in String.\nIndex: %d ", wrd, i);
         return 0;
      }
   }
   wrd[slen - 1] = wrd[slen];
   printf("\nWord \"%s\" is NOT Found in String", wrd);
   return 0;
}