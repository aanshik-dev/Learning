#include <stdio.h>

struct proc {
  int pid;
  int at;
  int burst;
  int pr;
  int left;
  int end;
  int wait;
  int tat;
};

int main() {

  int n;
  printf("\nEnter the number of processes: ");
  scanf("%d", &n);

  struct proc arr[n];

  printf("\nEnter the Process in format [PID  AT  BT  PR]\n");
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d %d", &arr[i].pid, &arr[i].at, &arr[i].burst, &arr[i].pr);
    arr[i].left = arr[i].burst;
  }

  int complete = 0, time = 0;
  int prev = -1;

  printf("\nGantt Chart:\n");

  while (complete < n) {

    int idx = -1;
    int best = 10000;

    for (int i = 0; i < n; i++) {

      if (arr[i].at <= time && arr[i].left > 0) {

        if (arr[i].pr < best) {
          best = arr[i].pr;
          idx = i;
        }

        if (arr[i].pr == best) {
          if (arr[i].at < arr[idx].at) {
            idx = i;
          }
        }
      }
    }

    if (idx != -1) {

      if (prev != idx) {
        if (prev != -1)
          printf("%d | ", time);

        printf("P%d (%d-", arr[idx].pid, time);
      }

      arr[idx].left--;
      time++;

      if (arr[idx].left == 0) {
        arr[idx].end = time;
        complete++;
      }

      prev = idx;

    } else {
      time++;
    }
  }

  printf("%d", time);

  float wait = 0, turnAT = 0;

  printf("\n\nPID  AT  BT  PR  WT  TAT\n");

  for (int i = 0; i < n; i++) {

    arr[i].tat = arr[i].end - arr[i].at;
    arr[i].wait = arr[i].tat - arr[i].burst;

    wait += arr[i].wait;
    turnAT += arr[i].tat;

    printf("P%d   %d   %d   %d   %d   %d\n", arr[i].pid, arr[i].at, arr[i].burst, arr[i].pr, arr[i].wait, arr[i].tat);
  }

  printf("\nAverage Waiting Time: %.2f\n", wait / n);
  printf("Average Turnaround Time: %.2f\n\n", turnAT / n);

  return 0;
}