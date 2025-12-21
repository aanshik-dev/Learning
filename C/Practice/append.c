#include <stdio.h>

void prtarr(int[], int);
void arrinsert(int[], int, int, int);

void prtarr(int *base, int size) {
   int *arr = base;
   for (int i = 0; i < size + 1; i++)
      printf("%d ", arr[i]);
   printf("\n\n");
}
void arrinsert(int ar[], int size, int value, int post) {
   if (post == size) {
      ar[post] = value;
      return;
   }
   int save = ar[post];
   ar[post++] = value;
   arrinsert(ar, size, save, post);
}

int main() {
   int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
   int size = sizeof(arr) / sizeof(int);
   printf("Size: %d\v\v  ", size);
   arrinsert(arr, size, 500, 3);
   prtarr(arr, size);

   return 0;
}
