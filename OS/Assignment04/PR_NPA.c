#include <stdio.h>

struct proc {
  int pid;
  int at;
  int burst;
  int pr;
  int end;
  int wait;
  int tat;
  int done;
};

int main() {

  int n;
  printf("\nEnter the number of processes: ");
  scanf("%d", &n);

  struct proc arr[n];

  printf("\nEnter the Process in format [PID  AT  BT  PR]\n");
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d %d", &arr[i].pid, &arr[i].at, &arr[i].burst, &arr[i].pr);
    arr[i].done = 0;
  }

  int complete = 0, time = 0;

  printf("\nGantt Chart:\n");

  while (complete < n) {

    int idx = -1;
    int best = 10000;

    for (int i = 0; i < n; i++) {

      if (arr[i].at <= time && arr[i].done == 0) {

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

      int start = time;

      time += arr[idx].burst;
      arr[idx].end = time;
      arr[idx].done = 1;
      complete++;

      printf("P%d (%d - %d) | ", arr[idx].pid, start, time);

      for (int i = 0; i < n; i++) {
        if (arr[i].at <= time && arr[i].done == 0) {
          arr[i].pr--;
        }
      }

    } else {
      time++;
    }
  }

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