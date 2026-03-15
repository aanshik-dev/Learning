#include <stdio.h>

struct proc {
  int pid;
  int at;
  int bt;
  int pr;
  int end;
  int wt;
  int tat;
  int done;
  int wait_time;
};

int main() {

  int n;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  struct proc p[n];

  printf("Enter PID AT BT PR\n");
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d %d", &p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
    p[i].done = 0;
    p[i].wait_time = 0;
  }

  int time = 0, complete = 0;

  printf("\nGantt Chart:\n");

  while (complete < n) {

    int idx = -1;
    int best = 10000;

    for (int i = 0; i < n; i++) {

      if (p[i].at <= time && p[i].done == 0) {

        if (p[i].pr < best) {
          best = p[i].pr;
          idx = i;
        }

        else if (p[i].pr == best) {
          if (p[i].at < p[idx].at)
            idx = i;
        }
      }
    }

    if (idx != -1) {

      int start = time;

      time += p[idx].bt;

      p[idx].end = time;
      p[idx].done = 1;
      complete++;

      printf("P%d (%d - %d) | ", p[idx].pid, start, time);

      for (int i = 0; i < n; i++) {

        if (i != idx && p[i].at <= time && p[i].done == 0) {

          p[i].wait_time += p[idx].bt;

          while (p[i].wait_time >= 5) {
            p[i].pr--;
            p[i].wait_time -= 5;
          }
        }
      }

    } else {
      time++;
    }
  }

  float awt = 0, atat = 0;

  printf("\n\nPID AT BT PR WT TAT\n");

  for (int i = 0; i < n; i++) {

    p[i].tat = p[i].end - p[i].at;
    p[i].wt = p[i].tat - p[i].bt;

    awt += p[i].wt;
    atat += p[i].tat;

    printf("P%d %d %d %d %d %d\n",
           p[i].pid, p[i].at, p[i].bt, p[i].pr, p[i].wt, p[i].tat);
  }

  printf("\nAverage Waiting Time: %.2f\n", awt / n);
  printf("Average Turnaround Time: %.2f\n", atat / n);

  return 0;
}