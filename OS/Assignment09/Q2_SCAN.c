#include <stdio.h>
#include <stdlib.h>

int main() {
  int n, head, disk_size, dir, total_movement = 0;

  printf("Enter number of requests: ");
  scanf("%d", &n);
  int req[n + 1];
  printf("Enter requests: ");
  for (int i = 0; i < n; i++)
    scanf("%d", &req[i]);

  printf("Enter initial head: ");
  scanf("%d", &head);
  printf("Enter disk size (max cylinder): ");
  scanf("%d", &disk_size);
  printf("Enter direction (0 for low, 1 for high): ");
  scanf("%d", &dir);

  // Sort requests
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (req[i] > req[j]) {
        int temp = req[i];
        req[i] = req[j];
        req[j] = temp;
      }
    }
  }

  int pos = 0;
  while (pos < n && req[pos] < head)
    pos++;

  printf("\nAlgorithm: SCAN\nSequence: ");
  if (dir == 1) {
    for (int i = pos; i < n; i++)
      printf("%d ", req[i]);
    printf("%d ", disk_size);
    for (int i = pos - 1; i >= 0; i--)
      printf("%d ", req[i]);
    total_movement = (disk_size - head) + (disk_size - req[0]);
  } else {
    for (int i = pos - 1; i >= 0; i--)
      printf("%d ", req[i]);
    printf("0 ");
    for (int i = pos; i < n; i++)
      printf("%d ", req[i]);
    total_movement = (head - 0) + (req[n - 1] - 0);
  }

  printf("\nTotal head movement: %d\n", total_movement);
  return 0;
}