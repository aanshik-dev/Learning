#include <stdio.h>

struct proc {
  int pid;
  int at;
  int burst;
  int end;
  int left;
  int wait;
  int tat;
};

int main() {
  int n;
  printf("\nEnter the number of processes: ");
  scanf("%d", &n);

  struct proc arr[n];

  printf("\nEnter the Process in format [PID  AT  BT]\n");
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &arr[i].pid, &arr[i].at, &arr[i].burst);
    arr[i].left = arr[i].burst;
  }

  int quant;
  printf("\nEnter the time quanta: ");
  scanf("%d", &quant);

  int complete = 0, time = 0;

  printf("\nGantt Chart:\n");
  while (complete < n) {

    int found = 0;
    for (int i = 0; i < n; i++) {
      if (arr[i].at <= time && arr[i].left > 0) {
        int start = time;
        found = 1;
        if (arr[i].left - quant > 0) {
          time += quant;
          arr[i].left -= quant;
        } else {
          time += arr[i].left;
          arr[i].left = 0;
          arr[i].end = time;
          complete++;
        }
        printf("P%d (%d - %d) | ", arr[i].pid, start, time);
      }
    }
    if (!found) {
      time++;
    }
  }

  float wait = 0, turnAT = 0;
  printf("\n\nPID  AT  BT  WT  TAT\n");
  for (int i = 0; i < n; i++) {
    arr[i].tat = arr[i].end - arr[i].at;
    arr[i].wait = arr[i].tat - arr[i].burst;
    wait += arr[i].wait;
    turnAT += arr[i].tat;

    printf("P%d   %d   %d   %d   %d\n", arr[i].pid, arr[i].at, arr[i].burst, arr[i].wait, arr[i].tat);
  }

  printf("\nAverage Waiting Time: %.2f\n", wait / n);
  printf("Average Turnaround Time: %.2f\n\n", turnAT / n);
  return 0;
}
