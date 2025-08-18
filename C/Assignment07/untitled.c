#include <stdio.h>
int binsearch(int *a, int n, int m) {
   int key = n / 2;
   for (int i = 0; i < n; i++) {
      if (a[key] == m) {
         printf("yes,%d is present in array at %d position ", m, key + 1);
         break;
      } else {
         if (m > a[key])
            key = (key + n) / 2;
         else
            key = key / 2;
      }
   }
}
int main() {
   int a[10] = {1, 3, 5, 7, 8, 9, 16, 20, 27, 28};
   binsearch(a, 6, 1);
}

#include <stdio.h>
int binsearch(int *a, int n, int m);

int main() {
   int a[14] = {1, 3, 5, 7, 8, 9, 16, 20, 27, 28, 29, 31, 32, 33};
   for (int i = 0; i < 35; i++)
      binsearch(a, 14, i);
}

int binsearch(int *a, int n, int m) {
   int right = n, left = 0;
   while (left <= right) {
      int mid = left + (right - left) / 2;
      if (a[mid] == m) {
         printf("%d:present at %d\n", m, mid + 1);
         return 0;
      } else if (m > a[mid]) {
         left = mid + 1;
      } else {
         right = mid - 1;
      }
   }
   printf("%d: Not present\n", m);
}