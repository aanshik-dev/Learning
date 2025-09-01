#include <stdio.h>

typedef struct pair {
  int x;
  int y;
} pair;

pair matBinSearch(int size, int arr[size][size], int r, int c, int trgt) {
  pair pair_idx;
  pair_idx.x = -1;
  pair_idx.y = -1;
  if (r >= 0 && r < size && c >= 0 && c < size) {
    if (arr[r][c] == trgt) {
      pair_idx.x = r;
      pair_idx.y = c;
    } else if (trgt > arr[r][c]) {
      pair_idx = matBinSearch(size, arr, r + 1, c, trgt);
    } else if (trgt < arr[r][c]) {
      pair_idx = matBinSearch(size, arr, r, c - 1, trgt);
    }
  }
  return pair_idx;
}

int main() {
  int size, trgt;
  printf("\nPlease enter the size of the matrix: ");
  scanf("%d", &size);
  int arr[size][size];
  for (int i = 0; i < size; i++) {
    printf("Row [%d] : ", i + 1);
    for (int j = 0; j < size; j++) {
      scanf("%d", &arr[i][j]);
    }
  }
  printf("Please enter a target value: ");
  scanf("%d", &trgt);
  pair idx_pair = matBinSearch(size, arr, 0, size - 1, trgt);

  printf("The index is : (%d, %d)\n\n", idx_pair.x, idx_pair.y);
}