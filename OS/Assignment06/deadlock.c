#include <stdbool.h>
#include <stdio.h>

#define MAX_P 20
#define MAX_R 20

int main() {
  int n, m;
  int total[MAX_R];
  int allocation[MAX_P][MAX_R];
  int request[MAX_P][MAX_R];
  int available[MAX_R];
  bool finish[MAX_P];

  printf("Enter number of processes: ");
  scanf("%d", &n);

  printf("Enter number of resource types: ");
  scanf("%d", &m);

  printf("Enter total instances of each resource:\n");
  for (int i = 0; i < m; i++)
    scanf("%d", &total[i]);

  printf("Enter Allocation Matrix:\n");
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      scanf("%d", &allocation[i][j]);

  printf("Enter Request Matrix:\n");
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      scanf("%d", &request[i][j]);

  for (int j = 0; j < m; j++) {
    int sum = 0;
    for (int i = 0; i < n; i++)
      sum += allocation[i][j];

    available[j] = total[j] - sum;
  }

  for (int i = 0; i < n; i++)
    finish[i] = false;

  bool found = true;

  while (found) {
    found = false;

    for (int i = 0; i < n; i++) {
      if (!finish[i]) {
        int j;
        for (j = 0; j < m; j++) {
          if (request[i][j] > available[j])
            break;
        }

        if (j == m) {
          for (int k = 0; k < m; k++)
            available[k] += allocation[i][k];

          finish[i] = true;
          found = true;
        }
      }
    }
  }

  bool deadlock = false;

  for (int i = 0; i < n; i++) {
    if (!finish[i]) {
      deadlock = true;
      break;
    }
  }

  if (!deadlock) {
    printf("No deadlock exists\n");
  } else {
    printf("Deadlock exists\n");
    printf("Terminate processes: ");

    for (int i = 0; i < n; i++) {
      if (!finish[i])
        printf("P%d ", i);
    }

    printf("\n");
  }

  return 0;
}