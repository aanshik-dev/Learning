#include <stdio.h>
#pragma pack(1)

struct student {
   char name[11];
   int roll;
   char sex;
   double gpa;
};

int main() {

   struct student stud;

   printf("Address of stud: %u\n", &stud);
   printf("Address of stud.name: %u\n", &stud.name);
   printf("Address of stud.roll: %u\n", &stud.roll);
   printf("Address of stud.sex: %u\n", &stud.sex);
   printf("Address of stud.gpa: %u\n", &stud.gpa);
   printf("Size of structure student: %lu bytes\n", sizeof(struct student));

   return 0;
}