#include <stdio.h>
void rev(char *, int);
int main() {
   char str[100];
   printf("Please Enter a String\n");
   scanf(" %[^\n]s", str);
   printf("\nUser Input: %s\n", str);
   int w = 1, len = 0, ws;
   // this  one is example of test
   for (int i = 0; str[i] != '\0'; i++) {
      if (str[i] == ' ' && str[i + 1] != ' ') {
         w++;
         if (w % 2 == 0) {
            ws = i + 1;
            for (int j = i + 1; str[j] != ' ' && str[j] != '\0'; j++) {
               len++;
            }
            if (len % 2 == 1) {
               rev(&str[ws], len - 1);
            }
         }
         len = 0;
      }
   }
   printf("Final Output: %s\n\n", str);
   return 0;
}

void rev(char *w, int len) {
   char s;
   for (int i = 0; i <= len / 2; i++) {
      s = w[i];
      w[i] = w[len - i];
      w[len - i] = s;
   }
}