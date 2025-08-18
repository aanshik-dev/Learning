#include <stdio.h>
#pragma pack(1)

struct student {
  char name[11];
  int roll;
  char sex;
  double gpa;
};

void prt_stud(struct student s) {
  printf("Name : %s\n", s.name);
  printf("Roll Number : %d\n", s.roll);
  printf("Sex : %c\n", s.sex);
  printf("GPA : %.2f\n", s.gpa);
}

int main() {

  struct student students[5];

  for (int i = 0; i < 5; i++) {
    printf("Enter details for student %d:\n", i + 1);
    printf("Name : ");
    scanf("%10s", students[i].name);
    printf("Roll Number : ");
    scanf("%d", &students[i].roll);
    printf("Sex (M/F/T) : ");
    scanf(" %c", &students[i].sex);
    printf("GPA : ");
    scanf("%lf", &students[i].gpa);
  }

  for (int i = 0; i < 5; i++) {
    printf("\nDetails of student %d:\n", i + 1);
    prt_stud(students[i]);
    printf("Address of students[%d]: %u\n", i, &students[i]);
  }

  return 0;
}