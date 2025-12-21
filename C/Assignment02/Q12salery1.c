#include <stdio.h>
int main() {
   float sal, hra, da, gross;
   printf("Please Enter Base Salary: ");
   scanf("%f", &sal);

   if (sal > 0) {
      if (sal >= 0 && sal <= 30000) {
         hra = 0.20 * sal;
         da = 0.30 * sal;
      } else if (sal > 30000 && sal <= 60000) {
         hra = 0.25 * sal;
         da = 0.35 * sal;
      } else if (sal > 60000) {
         hra = 0.30 * sal;
         da = 0.40 * sal;
      }
      gross = sal + hra + da;
      printf("Base Salary: %0.2f\n", sal);
      printf("HRA on Base Salary: %0.2f\n", hra);
      printf("DA on Base Salary: %0.2f\n", da);
      printf("Gross Salary: %0.2f\n", gross);
   } else {
      printf("Entered Amount %f is Invalid", sal);
   }
}
