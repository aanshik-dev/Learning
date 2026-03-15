#include <stdio.h>

struct proc {
  int pid;
  int at;
  int burst;
  int rem;
  int end;
  int wait;
  int tat;
};

int main() {

  int n;
  printf("\nEnter number of processes: ");
  scanf("%d", &n);

  struct proc p[n];

  printf("\nEnter the Process in format [PID  AT  BT]\n");
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].burst);
    p[i].rem = p[i].burst;
  }

  int complete = 0, time = 0;
  float waiting = 0, turnAT = 0;

  int prev = -1;
  int start;

  printf("\nGantt Chart:\n");

  while (complete < n) {

    int idx = -1;
    int minBT = 10000;

    for (int i = 0; i < n; i++) {
      if (p[i].at <= time && p[i].rem > 0) {

        if (p[i].rem < minBT) {
          minBT = p[i].rem;
          idx = i;
        }

        if (p[i].rem == minBT) {
          if (p[i].at < p[idx].at) {
            idx = i;
          }
        }
      }
    }

    if (idx != -1) {

      if (prev != idx) {
        if (prev != -1) {
          printf("%d) | ", time);
        }
        printf("P%d (%d-", p[idx].pid, time);
        start = time;
      }

      p[idx].rem--;
      time++;

      if (p[idx].rem == 0) {

        complete++;

        p[idx].end = time;
        p[idx].tat = p[idx].end - p[idx].at;
        p[idx].wait = p[idx].tat - p[idx].burst;

        waiting += p[idx].wait;
        turnAT += p[idx].tat;
      }
      prev = idx;

    } else {
      time++;
    }
  }

  printf("%d", time);

  printf("\n\nPID   AT   BT   WT   TAT\n");

  for (int i = 0; i < n; i++) {
    printf("P%d  %d  %d  %d  %d\n", p[i].pid, p[i].at, p[i].burst, p[i].wait, p[i].tat);
  }

  printf("\nAverage Waiting Time: %.2f\n", waiting / n);
  printf("Average Turnaround Time: %.2f\n\n", turnAT / n);

  return 0;
}