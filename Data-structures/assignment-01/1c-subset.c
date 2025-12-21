#include <stdio.h>

int main() {
   int a, b, flag = 0;
   printf("Enter size of Super Set: ");
   scanf(" %d", &a);
   int sup[a];
   printf("Enter Super Set: ");
   for (int i = 0; i < a; i++) {
      scanf(" %d", &sup[i]);
   }
   printf("Enter size of Set: ");
   scanf(" %d", &b);
   int set[b];
   printf("Enter Set: ");
   for (int i = 0; i < b; i++) {
      scanf(" %d", &set[i]);
   }
   for (int i = 0; i < b; i++) {
      for (int j = 0; j < a; j++) {
         if (set[i] == sup[j]) {
            flag = 1;
            break;
         }
      }
      if (flag == 0) {
         printf("Not a subset of given array");
         return 0;
      }
      flag = 0;
   }
   printf("It is a subset of given array");

   return 0;
}