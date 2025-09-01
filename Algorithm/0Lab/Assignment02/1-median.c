#include <limits.h>
#include <stdio.h>

float medFind(int *arrA, int *arrB, int sizeA, int sizeB) {
  if (sizeB < sizeA) {
    int *temp = arrA;
    arrA = arrB;
    arrB = temp;
    int tempSize = sizeA;
    sizeA = sizeB;
    sizeB = tempSize;
  }

  int low = 0, high = sizeA;

  float median;

  while (1) {
    int partA = (high + low) / 2;
    int partB = (sizeA + sizeB + 1) / 2 - partA;
    int preA = (partA == 0) ? INT_MIN : arrA[partA - 1];
    int sucA = (partA == sizeA) ? INT_MAX : arrA[partA];
    int preB = (partB == 0) ? INT_MIN : arrB[partB - 1];
    int sucB = (partB == sizeB) ? INT_MAX : arrB[partB];
    if (preA <= sucB && preB <= sucA) {
      if ((sizeA + sizeB) % 2 == 0) {
        int a = preA > preB ? preA : preB;
        int b = sucA < sucB ? sucA : sucB;
        median = (float)(a + b) / 2.0;
      } else {
        median = (float)(preA > preB ? preA : preB);
      }
      break;
    } else if (preA > sucB) {
      high = partA - 1;
    } else if (preB > sucA) {
      low = partA + 1;
    }
  }

  return median;
}

int main() {
  int sizeA, sizeB;
  printf("\nPlease enter the size of the arrays: ");
  scanf("%d", &sizeA);
  scanf("%d", &sizeB);
  int arrA[sizeA], arrB[sizeB];
  printf("Please enter the array A: ");
  for (int i = 0; i < sizeA; i++) {
    scanf("%d", &arrA[i]);
  }
  printf("Please enter the array B: ");
  for (int i = 0; i < sizeB; i++) {
    scanf("%d", &arrB[i]);
  }

  float median = medFind(arrA, arrB, sizeA, sizeB);
  printf("The median is : %.2f\n\n", median);
}