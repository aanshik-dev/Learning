#include <stdio.h>
#pragma pack(1)

struct student {
   char name[11];
   int roll;
   char sex;
   double gpa;
};

void prtstud_ptr(struct student *s) {
   printf("Name: %s\n", s->name);
   printf("Roll: %d\n", s->roll);
   printf("Sex: %c\n", s->sex);
   printf("GPA: %.2f\n", s->gpa);
}

int main() {

   struct student stud;

   printf("Enter details for student\n");
   printf("Name : ");
   scanf("%10s", stud.name);
   printf("Roll Number : ");
   scanf("%d", &stud.roll);
   printf("Sex (M/F/T) : ");
   scanf(" %c", &stud.sex);
   printf("GPA : ");
   scanf("%lf", &stud.gpa);

   printf("\nPrinting stud using pointer\n");
   prtstud_ptr(&stud);

   return 0;
}