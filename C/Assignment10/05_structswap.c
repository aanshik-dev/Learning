#include <stdio.h>

struct point {
   int x;
   int y;
};

void swap(struct point *p1, struct point *p2) {
   struct point temp;
   temp = *p1;
   *p1 = *p2;
   *p2 = temp;
}

int main() {

   struct point p1, p2;
   printf("Enter X & Y co-ordinates of PointA : ");
   scanf("%d %d", &p1.x, &p1.y);

   printf("Enter X & Y co-ordinates of PointB : ");
   scanf("%d %d", &p2.x, &p2.y);

   printf("\nBefore Swaping:\n");
   printf("Point A: (%d, %d)\n", p1.x, p1.y);
   printf("Point B: (%d, %d)\n", p2.x, p2.y);

   swap(&p1, &p2);

   printf("\nAfter Swaping:\n");
   printf("Point A: (%d, %d)\n", p1.x, p1.y);
   printf("Point B: (%d, %d)\n", p2.x, p2.y);

   return 0;
}