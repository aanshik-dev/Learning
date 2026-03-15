#include <stdio.h>

struct proc {
  int pid;
  int at;
  int burst;
  int start;
  int end;
  int wait;
  int tat;
  int over;
};

int main() {
  int n;
  printf("\nEnter number of processes: ");
  scanf("%d", &n);

  struct proc p[n];

  printf("\nEnter the Process in format [PID  AT  BT]\n");
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].burst);
    p[i].over = 0;
  }

  int complete = 0, time = 0;
  float waiting = 0, turnAT = 0;

  printf("\nGantt Chart:\n");

  while (complete < n) {

    int idx = -1;
    int minBT = 10000;

    for (int i = 0; i < n; i++) {
      if (p[i].at <= time && p[i].over == 0) {
        if (p[i].burst < minBT) {
          minBT = p[i].burst;
          idx = i;
        }
        if (p[i].burst == minBT) {
          if (p[i].at < p[idx].at) {
            idx = i;
          }
        }
      }
    }

    if (idx != -1) {

      p[idx].start = time;
      p[idx].end = p[idx].start + p[idx].burst;
      p[idx].tat = p[idx].end - p[idx].at;
      p[idx].wait = p[idx].start - p[idx].at;

      waiting += p[idx].wait;
      turnAT += p[idx].tat;

      printf("P%d (%d-%d) | ", p[idx].pid, p[idx].start, p[idx].end);

      time = p[idx].end;
      p[idx].over = 1;
      complete++;
    } else {
      time++;
    }
  }

  printf("\n\nPID   AT   BT   WT   TAT\n");

  for (int i = 0; i < n; i++) {
    printf("P%d  %d  %d  %d  %d\n", p[i].pid, p[i].at, p[i].burst, p[i].wait, p[i].tat);
  }

  printf("\nAverage Waiting Time: %.2f\n", waiting / n);
  printf("Average Turnaround Time: %.2f\n\n", turnAT / n);

  return 0;
}