#include <stdio.h>

struct proc {
  int pid;
  int at;
  int bt;
  int pr;
  int left;
  int end;
  int wt;
  int tat;
  int last_wait;
};

int main() {

  int n;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  struct proc p[n];

  printf("Enter PID AT BT PR\n");
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d %d", &p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
    p[i].left = p[i].bt;
    p[i].last_wait = 0;
  }

  int time = 0, complete = 0;
  int prev = -1;

  printf("\nGantt Chart:\n");

  while (complete < n) {

    int idx = -1;
    int best = 10000;

    for (int i = 0; i < n; i++) {

      if (p[i].at <= time && p[i].left > 0) {

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

      if (prev != idx) {
        if (prev != -1)
          printf("%d | ", time);

        printf("P%d (%d-", p[idx].pid, time);
      }

      p[idx].left--;
      time++;

      for (int i = 0; i < n; i++) {

        if (i != idx && p[i].at <= time && p[i].left > 0) {

          p[i].last_wait++;

          if (p[i].last_wait == 5) {
            p[i].pr--;
            p[i].last_wait = 0;
          }
        }
      }

      if (p[idx].left == 0) {
        p[idx].end = time;
        complete++;
      }

      prev = idx;
    } else {
      time++;
    }
  }

  printf("%d\n", time);

  float awt = 0, atat = 0;

  printf("\nPID AT BT PR WT TAT\n");

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