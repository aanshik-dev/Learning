#include <stdio.h>
#include <stdlib.h>

int main() {

  int fr;
  printf("Enter the number of the Physical Frames : ");
  scanf("%d", &fr);

  printf("Enter the number of pages requested : ");
  int p;
  scanf("%d", &p);

  printf("Enter the page access string : ");
  int seq[p];
  for (int i = 0; i < p; i++) {
    scanf("%d", &seq[i]);
  }

  int frame[fr], time[fr];
  for (int i = 0; i < fr; i++) {
    frame[i] = -1;
    time[i] = 0;
  }

  int clock = 0, faults = 0;
  int data[p][fr];
  int miss[p];

  for (int i = 0; i < p; i++) {
    clock++;
    int hit = 0;

    for (int j = 0; j < fr; j++) {
      if (frame[j] == seq[i]) {
        time[j] = clock;
        hit = 1;
        break;
      }
    }

    if (!hit) {
      int pos = -1;
      for (int j = 0; j < fr; j++) {
        if (frame[j] == -1) {
          pos = j;
          break;
        }
      }

      if (pos == -1) {
        int min = time[0];
        pos = 0;
        for (int j = 1; j < fr; j++) {
          if (time[j] < min) {
            min = time[j];
            pos = j;
          }
        }
      }

      frame[pos] = seq[i];
      time[pos] = clock;
      faults++;
    }

    hit ? (miss[i] = 0) : (miss[i] = 1);

    for (int j = 0; j < fr; j++) {
      data[i][j] = frame[j];
    }
  }

  int clk;
  printf("Enter the clock cycle: ");
  scanf("%d", &clk);

  if (clk > p) {
    printf("Invalid Clock Access !!\n");
    exit(0);
  }

  int curFault = 0;
  printf("\n");
  for (int i = 0; i < clk; i++) {
    printf("Clock[%0.2d] : ", i + 1);
    for (int j = 0; j < fr; j++) {
      if (data[i][j] == -1) {
        printf("_ ");
      } else {
        printf("%d ", data[i][j]);
      }
    }
    curFault += miss[i];
    if (!miss[i])
      printf("  -> Hit\n");
    else
      printf("  -> Miss\n");
  }

  printf("\nClock[%d] : ", clk);
  for (int i = 0; i < fr; i++) {
    if (data[clk - 1][i] == -1) {
      printf("_ ");
    } else {
      printf("%d ", data[clk - 1][i]);
    }
  }
  printf("\nPage Faults = %d || Page Hit = %d\n\n", curFault, clk - curFault);

  printf("Total Fage Faults: %d\n\n", faults);
  return 0;
}

// 1 2 6 3 5 6 2 8 9 4 5 7 2 3 6 5 4 9 3 5