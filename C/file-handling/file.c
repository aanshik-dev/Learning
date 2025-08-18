#include <stdio.h>

int main() {
   FILE *fc, *fp;
   char ch;
   fc = fopen("PR1.txt", "r");
   if (fc == NULL) {
      printf("Error in opening file");
      return -1;
   }
   fp = fopen("Paste.txt", "w");
   if (fp == NULL) {
      printf("Error in opening file");
      return -1;
   }
   for (int i = 0;; i++) {
      ch = fgetc(fc);
      if (ch == EOF)
         break;
      fputc(ch, fp);
   }
   fclose(fp);
   fp = fopen("Paste.txt", "r");
   if (fp == NULL) {
      printf("Error in opening file");
      return -1;
   }
   while (1) {
      ch = fgetc(fp);
      if (ch == EOF)
         break;
      printf("%c", ch);
   }
   fclose(fc);
   fclose(fp);
   return 0;
}
