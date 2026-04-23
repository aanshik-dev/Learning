#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int n, head, total_movement = 0;
  printf("Enter number of requests: ");
  scanf("%d", &n);

  int req[n], visited[n];
  printf("Enter requests: ");
  for (int i = 0; i < n; i++) {
    scanf("%d", &req[i]);
    visited[i] = 0;
  }

  printf("Enter initial head position: ");
  scanf("%d", &head);

  printf("\nAlgorithm: SSTF\nSequence: ");
  for (int i = 0; i < n; i++) {
    int min_dist = INT_MAX;
    int index = -1;

    for (int j = 0; j < n; j++) {
      if (!visited[j]) {
        int dist = abs(req[j] - head);
        if (dist < min_dist) {
          min_dist = dist;
          index = j;
        }
      }
    }

    visited[index] = 1;
    total_movement += min_dist;
    head = req[index];
    printf("%d ", head);
  }

  printf("\nTotal head movement: %d\n", total_movement);
  return 0;
}