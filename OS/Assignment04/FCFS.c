#include <stdio.h>

struct proc {
  int pid;
  int at;
  int burst;
  int start;
  int end;
  int wait;
  int tat;
};

int main() {

  int n;
  printf("\nEnter number of processes: ");
  scanf("%d", &n);

  struct proc p[n], temp;

  printf("\nEnter the Process in format [PID  AT  BT]\n");
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].burst);
  }

  // Sort by Arrival Time
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (p[i].at > p[j].at) {
        temp = p[i];
        p[i] = p[j];
        p[j] = temp;
      }
    }
  }

  int time = 0;
  float waiting = 0, turnAT = 0;

  printf("\nGantt Chart:\n");

  for (int i = 0; i < n; i++) {

    if (time < p[i].at)
      time = p[i].at;

    p[i].start = time;
    p[i].end = p[i].start + p[i].burst;

    p[i].tat = p[i].end - p[i].at;
    p[i].wait = p[i].start - p[i].at;

    waiting += p[i].wait;
    turnAT += p[i].tat;

    printf("P%d (%d-%d) | ", p[i].pid, p[i].start, p[i].end);

    time = p[i].end;
  }

  printf("\n\nPID   AT   BT   WT   TAT\n");

  for (int i = 0; i < n; i++) {
    printf("P%d  %d  %d  %d  %d\n", p[i].pid, p[i].at, p[i].burst, p[i].wait, p[i].tat);
  }

  printf("\nAverage Waiting Time: %.2f\n", waiting / n);
  printf("Average Turnaround Time: %.2f\n", turnAT / n);

  return 0;
}