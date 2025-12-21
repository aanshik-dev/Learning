
#include <stdio.h>

int main() {
   char name[50];

   FILE *fptr;
   fptr = fopen("stud.txt", "r");

   if (fptr == NULL) {
      printf("Error!");
      return 0;
   } else
      printf("Address: %u", fptr);

   printf("Enter a student name to edit profile\nName: ");
   scanf("%s", name);

   return 0;
}
