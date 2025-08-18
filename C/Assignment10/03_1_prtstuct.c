#include <stdio.h>
struct student {
   char name[11];
   int roll;
   char sex;
   double gpa;
};

void prt_stud(struct student s) {
   printf("\nName : %s\n", s.name);
   printf("Roll Number : %d\n", s.roll);
   printf("Sex : %c\n", s.sex);
   printf("GPA : %.2f\n", s.gpa);
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

   prt_stud(stud);

   return 0;
}
