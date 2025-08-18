// Write a function in C to add an element
// at the desired position of an array,
// considering it a list.

#include <stdio.h>

void prtarr(int[], int);
void arrinsert(int[], int, int, int);

void prtarr(int *base, int size) {
   for (int i = 0; i < size; i++)
      printf("%d ", base[i]);
   printf("\n");
}
void arrinsert(int ar[], int size, int value, int post) {
   if (post >= size) {
      ar[size] = value;
      return;
   }
   int save = ar[post];
   ar[post] = value;
   arrinsert(ar, size, save, ++post);
}

int main() {
   int post, val;
   printf("Please enter value to insert: ");
   scanf("%d", &val);
   printf("Enter the position: ");
   scanf("%d", &post);

   int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
   int size = sizeof(arr) / sizeof(int);

   printf("\nBefore Insertion:\n  ");
   prtarr(arr, size);
   arrinsert(arr, size, val, post - 1);
   printf("\nAfter Insertion:\n  ");
   prtarr(arr, size + 1);

   return 0;
}
