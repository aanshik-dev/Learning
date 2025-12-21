#include <math.h>
#include <stdio.h>
struct point {
   int x;
   int y;
};
float dist(struct point, struct point);

int main() {

   struct point pointA, pointB;

   printf("Enter X co-ordinate of Point A: ");
   scanf("%d", &pointA.x);
   printf("Enter Y co-ordinate of Point A: ");
   scanf("%d", &pointA.y);

   printf("Enter X co-ordinate of Point B: ");
   scanf("%d", &pointB.x);
   printf("Enter Y co-ordinate of Point B: ");
   scanf("%d", &pointB.y);

   printf("\nDistance: %0.2f", dist(pointA, pointB));

   return 0;
}

float dist(struct point pt1, struct point pt2) {
   float dist = sqrt((pt1.x - pt2.x) * (pt1.x - pt2.x) + (pt1.y - pt2.y) * (pt1.y - pt2.y));
   return dist;
}
