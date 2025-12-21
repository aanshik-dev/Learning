#include <stdio.h>

union Data {
   char c;
   int i;
   float f;
   double d;
};

int main() {

   union Data data;

   printf("Address of char variable: %u\n", &data.c);
   printf("Address of int variable: %u\n", &data.i);
   printf("Address of float variable: %u\n", &data.f);
   printf("Address of double variable: %u\n\n", &data.d);

   printf("Size of union: %lu\n\n", sizeof(union Data));

   union Data data2 = {0};
   data2.c = 'A';
   printf("char: %c\nint: %d\nfloat: %f\ndouble: %f\n\n", data2.c, data2.i, data2.f, data2.d);

   union Data data3 = {0};
   data3.i = 90;
   printf("int: %d\nchar: %c\nfloat: %f\ndouble: %f\n\n", data3.i, data3.c, data3.f, data3.d);

   union Data *ptr = &data;
   ptr->c = '&';
   printf("char: %c\nint: %d\nfloat: %f\ndouble: %f\n\n", ptr->c, ptr->i, ptr->f, ptr->d);

   return 0;
}